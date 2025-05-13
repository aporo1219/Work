//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include"circle.h"
#include"enemy.h"
#include"obstacles.h"


//extern(スコア）の初期化
int GSCORE{ 0 };

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p) {
	base.emplace_back((unique_ptr<Base>)new CEnemy(400,200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_LEFT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_DOWN(400, 200));
}

//更新処理
int CGame::Update() {
        
	//クリックした場合
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !mouse_left)
		{
			int x,y;
			GetMousePoint(&x, &y);
			base.emplace_back((unique_ptr<Base>)new CCircle(x, y));
			
		}
		
	}
	//listオブジェクトの更新処理
	for (auto i = base.begin(); i != base.end(); i++)
		(*i)->Action(base);

	//リストのサイズ保存
	temp_list_Length = (int)base.size();

	//リストからのオブジェクト削除処理
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//マウスの左クリック状態を保存
	mouse_left = (GetMouseInput() & MOUSE_INPUT_LEFT);
	return 0;
}

//描画処理
void CGame::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "List_Size = %d", base.size());
	DrawFormatString(0, 16, GetColor(255, 255, 255), "SCORE = %d", GSCORE);
	
	//listオブジェクトの描画
	for (auto i = base.begin(); i != base.end(); i++)
		if ((*i)->FLAG) (*i)->Draw();

	//3D軸の描画
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 0, 100),
	//	0x0000ff
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(100, 0, 0),
	//	0xff0000
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 100, 0),
	//	0x00ff00
	//);
}

CGame::~CGame()
{

}
