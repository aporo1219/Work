//enemy.cpp
#include"enemy.h"
#include"function.h"
#include"obstacles.h"

//重力加速度
constexpr auto g = 0.98f;

CEnemy::CEnemy(int x, int y)
{
	radius = 32.0f;

	//初期位置
	pos.x = x;
	pos.y = y;

	vec.x = 0.2f;
	vec.y = 0.5f;

	vec = Vector_SetLength(vec, 30.0f);

	ID = ENEMY;
}

int CEnemy::Action(list<unique_ptr<Base>>& base)
{
	
	pos.x += vec.x;
	pos.y += vec.y;

	for (auto i = base.begin();i != base.end();i++)
	{


		//障害物左上
		if ((*i)->ID == OBSTACLES_LEFT_UP)
		{
			float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//障害物左上の情報を見ることができる
			float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
			if (distanceO_L_U < radius + O_L_U)
			{
				vec.y = -vec.y;//ベクトルを逆にする
				vec.y += 5.0;
				break;
			}
		}

		//障害物右上
		else if ((*i)->ID == OBSTACLES_RIGHT_UP)
		{
			float O_R_U = ((CObstacles_RIGHT_UP*)(*i).get())->radius;//障害物右上の情報を見ることができる
			float distanceO_R_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
			if (distanceO_R_U < radius + O_R_U)
			{
				vec.y = -vec.y;//ベクトルを逆にする
				vec.y += 5.0;
				break;
			}
		}

		//障害物右下
		else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
		{
			float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//障害物右下の情報を見ることができる
			float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
			if (distanceO_R_D < radius + O_R_D)
			{
				
				vec.y = -vec.y;//ベクトルを逆にする
				vec.y += 5.0;
				break;
			}
		}
	}

	if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
	{
		vec.x = -vec.x;
		
	}

	//画面の下で跳ね返る
	if (pos.y > WINDOW_HEIGHT - radius||pos.y<radius)
	{
		vec.y = -vec.y;//ベクトルを逆にする
	}

	return 0;
}

void CEnemy::Draw()
{
	DrawCircle(
		pos.x, pos.y,          //中心座標
		radius,               //半径
		GetColor(255, 0, 0),//色
		false               //塗りつぶし(false/true)
	);

}