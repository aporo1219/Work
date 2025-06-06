#include <iostream>
#include <Windows.h>
#include <gdiplus.h>	//GDI+���g�p
#include <XInput.h>
#pragma comment (lib, "gdiplus.lib") //GDI+��lib�ǂݍ���
#pragma comment(lib,"xinput.lib ")	 //XInput��lib�ǂݍ���

using namespace std;

constexpr int WIN_HEIGHT{ 480 };
constexpr int WIN_WIDTH { 640 };
constexpr int WIN_RGB   { 3   };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//RGB�N���X<�R�R�I
class C_RGB
{
public:
	int r;
	int g;
	int b;
};

int g_x = 0;
int g_y = 0;

//XInput�萔
constexpr auto MAX_CONTROLERS{ 4 };
constexpr auto THRESHOLD{ 32767.0f }; //�W���C�X�e�B�b�N�̂������l

//�T�C�Y���o�b�t�@��p�ӂ���<�R�R�I
C_RGB img64[64][64];

//�E�B���h�E�֘A
HWND	g_hWnd;					//�E�B���h�E�n���h��
MSG		g_msg;					//���b�Z�[�W
//�o�b�N�o�b�t�@�E�B���h�E�֘A�n���h��
HDC		g_pBackBufferHdc;		//�E�B���h�E�n���h��
HBITMAP	g_pBackBufferBitMap;	//�r�b�g�}�b�v�n���h��
LPBYTE	g_pBackBufferPixel;		//�s�N�Z���|�C���^

//�h���[�|�C���g�֐�
//�w�肵���o�b�t�@�̈ʒu��RGB�̓_��ł�
//x=X�ʒu,y=Y�ʒu,r=��,g=��,b=��,pb=�_��ło�b�t�@
void DrawPoint(int x, int y, int r, int g, int b, LPBYTE pb)
{
	//���_������ɕύX
	y = WIN_HEIGHT - y;

	//�_��ł�
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 0] = (BYTE)b;
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 1] = (BYTE)g;
	pb[(y * (WIN_WIDTH * WIN_RGB)) + (x * WIN_RGB) + 2] = (BYTE)r;
	return;
}

//XBOX360��p�R���g���[���[�X�e�[�^�X
struct CONTROLER_STATE
{
	XINPUT_STATE	m_state;		//�R���g���[���[�X�e�[�^�X
	bool			m_bConnected;	//�ڑ����
};

//XInputXBOX360��p�R���g���[���[�p�b�g
CONTROLER_STATE GAME_PAD[MAX_CONTROLERS];

//���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WCHAR name[] = { L"POINT" };	//�E�B���h�E���^�C�g���l�[��
	//�E�B���h�E�X�e�[�^�X
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),CS_HREDRAW | CS_VREDRAW,
		WndProc,0, 0,hInstance,NULL, NULL,
		(HBRUSH)(COLOR_WINDOW + 1),NULL,name,NULL
	};

	//�E�B���h�E�N���X�쐬
	RegisterClassEx(&wcex);
	int width = WIN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height= WIN_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	//�E�B���h�E�쐬
	if (!(g_hWnd = CreateWindow(name, name,
		WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX),
		CW_USEDEFAULT, 0, width+10, height+10, 0, 0, hInstance, 0)))
	{
		return 0;
	}

	ShowWindow(g_hWnd, SW_SHOW);

	//�o�b�N�o�b�t�@�X�e�[�^�X�ݒ�
	BITMAPINFO	BackBI{0};
	BackBI.bmiHeader.biWidth    = WIN_WIDTH;	//����
	BackBI.bmiHeader.biHeight   = WIN_HEIGHT;	//����
	BackBI.bmiHeader.biBitCount = WIN_RGB * 8;	//�F�̃r�b�g��
	BackBI.bmiHeader.biSize		= 40;
	BackBI.bmiHeader.biSizeImage = WIN_WIDTH * WIN_HEIGHT * WIN_RGB;//�C���[�W�T�C�Y
	BackBI.bmiHeader.biPlanes	= 1;
	BackBI.bmiHeader.biXPelsPerMeter = BackBI.bmiHeader.biYPelsPerMeter = 3780;
	//�o�b�N�o�b�t�@�쐬
	HDC hdc = GetDC(g_hWnd);
	g_pBackBufferHdc = CreateCompatibleDC(hdc);
	g_pBackBufferBitMap = CreateDIBSection(hdc, &BackBI, DIB_RGB_COLORS, (void**)&g_pBackBufferPixel, NULL, 0);
	SelectObject(g_pBackBufferHdc, g_pBackBufferBitMap);
	ReleaseDC(g_hWnd, hdc);

	//�����ŁA�O���t�B�b�N�f�[�^�����[�h���Ă��������B
	//�O���t�B�b�N�iRGB�̐F�z��̓O���[�o���ŕێ����邱�Ɓj
	//GDI+�̏����ݒ�<�R�R�I
	ULONG_PTR	gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	if (Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
	{
		return 1;
	}

	//�摜�t�@�C�����J���F�Ή��摜�`�� BMP, JPEG, PNG, GIF, TIFF, WMF, EMF�@<�R�R�I
	int img_width;
	int img_height;
	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(L"car.jpg");
	if (pBitmap->GetLastStatus() == Gdiplus::Ok)
	{
		//�ǂݍ��񂾃O���t�B�b�N�𕝁E����
		img_width = pBitmap->GetWidth();
		img_height = pBitmap->GetHeight();
	}
	else
	{
		return 2;
	}

	

	//GDI+�ŁA�O���t�B�b�N�ǂݍ��݁@<�R�R�I
	Gdiplus::Color  srcColor;
	for (int j = 0; j < 64; j++)
	{
		for (int i = 0; i < 64; i++)
		{
			//�O���t�B�b�N���f�[�^����1�s�N�Z���ۑ�
			pBitmap->GetPixel(i, j, &srcColor);
			img64[j][i].r = srcColor.GetR();
			img64[j][i].g = srcColor.GetG();
			img64[j][i].b = srcColor.GetB();
		}
	}

	HDC hdc_Primary = GetDC(g_hWnd);
	//���C�����[�v
	do
	{
		if (PeekMessage(&g_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
		}
		//�o�b�N�o�b�t�@�N���A
		memset(g_pBackBufferPixel, 0x00, WIN_WIDTH * WIN_HEIGHT * WIN_RGB);

		
		//�W���C�X�e�B�b�N�̏�Ԏ擾
		DWORD dwResult;
		for (DWORD i = 0; i < MAX_CONTROLERS; i++)
		{
			dwResult = XInputGetState(i, &GAME_PAD[i].m_state);
			if (dwResult == ERROR_SUCCESS)
				GAME_PAD[i].m_bConnected = true;
			else
				GAME_PAD[i].m_bConnected = false;
		}

		//�v���C���[�P�̃W���C�X�e�B�b�N�̃A�i���O�R���g���[���[���擾
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

		//�ۑ������O���t�B�b�N�f�[�^���g���ĕ`��@<�R�R�I
		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 64; i++)
			{
				DrawPoint(100 + i, 100 + j, img64[j][i].r, img64[j][i].g, img64[j][i].b, g_pBackBufferPixel);
			}
		}

		//�v���C�}���[�o�b�t�@�ɃX���b�v
		BitBlt(hdc_Primary, 0, 0, WIN_WIDTH, WIN_HEIGHT, g_pBackBufferHdc, 0, 0, SRCCOPY);
	} while (g_msg.message != WM_QUIT);

	Gdiplus::GdiplusShutdown(gdiplusToken);//<�R�R�I
	ReleaseDC(g_hWnd, hdc_Primary);
	DeleteObject(g_pBackBufferPixel);
	DeleteDC(g_pBackBufferHdc);
	return 0;
};

//�R�[���o�b�N�֐�
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
		case VK_ESCAPE://ESC�L�[�ŏI��
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CLOSE:			// �E�B���h�E�����ꍇ
		PostQuitMessage(0);
	case WM_DESTROY:		// �I������ꍇ
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}