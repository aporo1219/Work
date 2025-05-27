//ゲームシーン
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include"circle.h"
#include"enemy.h"
#include"obstacles.h"
#include"dispenser.h"




//extern(スコア）の初期化
int GSCORE{ 0 };
bool VANISH{ true };
int GLIFE{ 5 };


void GameOver();

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p) {
	base.emplace_back((unique_ptr<Base>)new CEnemy(400,200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_LEFT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_DOWN(400, 200));
	base.emplace_back((unique_ptr<Base>)new CDispenser(400, 200));
}

//更新処理
int CGame::Update() {
	if (GLIFE <= 0)
	{
		GameOver();
		
		
	}
	
	//クリックした場合
	{
		
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !mouse_left && VANISH == true && GLIFE > 0)
		{
			int x,y;
			GetMousePoint(&x, &y);
			base.emplace_back((unique_ptr<Base>)new CCircle(x, y));
			VANISH = false;
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
	DrawFormatString(400, 0, GetColor(255, 255, 0), "SCORE = %d", GSCORE);
	DrawFormatString(400, 16, GetColor(0, 255, 0), "ライフ = %d", GLIFE);
	DrawFormatString(400, 32, GetColor(255, 255, 255), "黄色は反発力が高い");
	DrawFormatString(400, 48, GetColor(255, 255, 255), "赤はスコアとライフが減少");
	DrawFormatString(400, 64, GetColor(255, 255, 255), "青はライフを回復");
	DrawFormatString(400, 80, GetColor(255, 255, 255), "動いている円はスコアアップ");
	DrawBox(400, 0, 650, 100, GetColor(0, 255, 255), false);
	
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

void GameOver()
{	 
	DrawString(400, 160, "そこまで" ,GetColor(255, 255, 255));
	DrawFormatString(400, 176, GetColor(255, 0, 0),"スコアは%dです。",GSCORE);
}
