#include <iostream>
#include <Windows.h>
#include <gdiplus.h>	//GDI+を使用
#include <XInput.h>
#pragma comment (lib, "gdiplus.lib") //GDI+のlib読み込み
#pragma comment(lib,"xinput.lib ")	 //XInputのlib読み込み

using namespace std;

constexpr int WIN_HEIGHT{ 480 };
constexpr int WIN_WIDTH { 640 };
constexpr int WIN_RGB   { 3   };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//RGBクラス<ココ！
class C_RGB
{
public:
	int r;
	int g;
	int b;
};

int g_x = 0;
int g_y = 0;

//XInput定数
constexpr auto MAX_CONTROLERS{ 4 };
constexpr auto THRESHOLD{ 32767.0f }; //ジョイスティックのしきい値

//サイズ分バッファを用意する<ココ！
C_RGB img64[64][64];

//ウィンドウ関連
HWND	g_hWnd;					//ウィンドウハンドル
MSG		g_msg;					//メッセージ
//バックバッファウィンドウ関連ハンドル
HDC		g_pBackBufferHdc;		//ウィンドウハンドル
HBITMAP	g_pBackBufferBitMap;	//ビットマップハンドル
LPBYTE	g_pBackBufferPixel;		//ピクセルポインタ

//ドローポイント関数
//指定したバッファの位置にRGBの点を打つ
//x=X位置,y=Y位置,r=赤,g=緑,b=青,pb=点を打つバッファ
void DrawPoint(int x, int y, int r, int g, int b, LPBYTE pb)
{
	//原点を左上に変更
	y = WIN_HEIGHT - y;

	//点を打つ
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 0] = (BYTE)b;
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 1] = (BYTE)g;
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 2] = (BYTE)r;
	return;
}

//XBOX360専用コントローラーステータス
struct CONTROLER_STATE
{
	XINPUT_STATE	m_state;		//コントローラーステータス
	bool			m_bConnected;	//接続状態
};

//XInputXBOX360専用コントローラーパット
CONTROLER_STATE GAME_PAD[MAX_CONTROLERS];

//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WCHAR name[] = { L"POINT" };	//ウィンドウ＆タイトルネーム
	//ウィンドウステータス
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),CS_HREDRAW | CS_VREDRAW,
		WndProc,0, 0,hInstance,NULL, NULL,
		(HBRUSH)(COLOR_WINDOW + 1),NULL,name,NULL
	};

	//ウィンドウクラス作成
	RegisterClassEx(&wcex);
	int width = WIN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height= WIN_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	//ウィンドウ作成
	if (!(g_hWnd = CreateWindow(name, name,
		WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX),
		CW_USEDEFAULT, 0, width+10, height+10, 0, 0, hInstance, 0)))
	{
		return 0;
	}

	ShowWindow(g_hWnd, SW_SHOW);

	//バックバッファステータス設定
	BITMAPINFO	BackBI{0};
	BackBI.bmiHeader.biWidth    = WIN_WIDTH;	//横幅
	BackBI.bmiHeader.biHeight   = WIN_HEIGHT;	//高さ
	BackBI.bmiHeader.biBitCount = WIN_RGB * 8;	//色のビット数
	BackBI.bmiHeader.biSize		= 40;
	BackBI.bmiHeader.biSizeImage = WIN_WIDTH * WIN_HEIGHT * WIN_RGB;//イメージサイズ
	BackBI.bmiHeader.biPlanes	= 1;
	BackBI.bmiHeader.biXPelsPerMeter = BackBI.bmiHeader.biYPelsPerMeter = 3780;
	//バックバッファ作成
	HDC hdc = GetDC(g_hWnd);
	g_pBackBufferHdc = CreateCompatibleDC(hdc);
	g_pBackBufferBitMap = CreateDIBSection(hdc, &BackBI, DIB_RGB_COLORS, (void**)&g_pBackBufferPixel, NULL, 0);
	SelectObject(g_pBackBufferHdc, g_pBackBufferBitMap);
	ReleaseDC(g_hWnd, hdc);

	//ここで、グラフィックデータをロードしてください。
	//グラフィック（RGBの色配列はグローバルで保持すること）
	//GDI+の初期設定<ココ！
	ULONG_PTR	gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
	{
		return 1;
	}

	//画像ファイルを開く：対応画像形式 BMP, JPEG, PNG, GIF, TIFF, WMF, EMF　<ココ！
	int img_width;
	int img_height;
	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(L"car.jpg");
	if (pBitmap->GetLastStatus() == Gdiplus::Ok)
	{
		//読み込んだグラフィックを幅・高さ
		img_width = pBitmap->GetWidth();
		img_height = pBitmap->GetHeight();
	}
	else
	{
		return 2;
	}

	

	//GDI+で、グラフィック読み込み　<ココ！
	Gdiplus::Color  srcColor;
	for (int j = 0; j < 64; j++)
	{
		for (int i = 0; i < 64; i++)
		{
			//グラフィックをデータから1ピクセル保存
			pBitmap->GetPixel(i, j, &srcColor);
			img64[j][i].r = srcColor.GetR();
			img64[j][i].g = srcColor.GetG();
			img64[j][i].b = srcColor.GetB();
		}
	}

	HDC hdc_Primary = GetDC(g_hWnd);
	//メインループ
	do
	{
		if (PeekMessage(&g_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
		}
		//バックバッファクリア
		memset(g_pBackBufferPixel, 0x00, WIN_WIDTH * WIN_HEIGHT * WIN_RGB);

		
		//ジョイスティックの状態取得
		DWORD dwResult;
		for (DWORD i = 0; i < MAX_CONTROLERS; i++)
		{
			dwResult = XInputGetState(i, &GAME_PAD[i].m_state);
			if (dwResult == ERROR_SUCCESS)
				GAME_PAD[i].m_bConnected = true;
			else
				GAME_PAD[i].m_bConnected = false;
		}

		//プレイヤー１のジョイスティックのアナログコントローラー情報取得
		if (GAME_PAD[0].m_bConnected == true)
		{
			float w = ((float)GAME_PAD[0].m_state.Gamepad.sThumbLX) / THRESHOLD;
			if (w < -1.0f) w = -1.0f;
			if (w > +1.0f) w = +1.0f;
			g_x += w;
		}
		if (GAME_PAD[0].m_bConnected == true)
		{
			float w = ((float)GAME_PAD[0].m_state.Gamepad.sThumbLY) / THRESHOLD;
			if (w < -1.0f) w = -1.0f;
			if (w > +1.0f) w = +1.0f;
			g_y -= w;
		}

		//保存したグラフィックデータを使って描画　<ココ！
		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 64; i++)
			{
				DrawPoint(100 + i, 100 + j, img64[j][i].r, img64[j][i].g, img64[j][i].b, g_pBackBufferPixel);
			}
		}

		//プライマリーバッファにスワップ
		BitBlt(hdc_Primary, 0, 0, WIN_WIDTH, WIN_HEIGHT, g_pBackBufferHdc, 0, 0, SRCCOPY);
	} while (g_msg.message != WM_QUIT);

	Gdiplus::GdiplusShutdown(gdiplusToken);//<ココ！
	ReleaseDC(g_hWnd, hdc_Primary);
	DeleteObject(g_pBackBufferPixel);
	DeleteDC(g_pBackBufferHdc);
	return 0;
};

//コールバック関数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_MOUSEMOVE)
	{
		POINT point = { LOWORD(lParam), HIWORD((lParam)) };
	}

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if ((GetAsyncKeyState('W') & 0x800))
			g_y -= 1;
			break;
		case VK_DOWN:
			if ((GetAsyncKeyState('S') & 0x800))
			g_y += 1;
			break;
		case VK_LEFT:
			if ((GetAsyncKeyState('A') & 0x800))
			g_x -= 1;
			break;
		case VK_RIGHT:
			if ((GetAsyncKeyState('d') & 0x800))
			g_x += 1;
			break;
		case VK_ESCAPE://ESCキーで終了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CLOSE:			// ウィンドウを閉じる場合
		PostQuitMessage(0);
	case WM_DESTROY:		// 終了する場合
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}