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

	vec = Vector_SetLength(vec, 10.0f);

	ID = ENEMY;
	Vector_Normalize(vec);

}

int CEnemy::Action(list<unique_ptr<Base>>& base)
{
	if (GLIFE > 0)
	{
		float L = 0.0f;
		pos.x += vec.x;
		pos.y += vec.y;

		L = Vector_Length(vec);

		for (auto i = base.begin();i != base.end();i++)
		{


			//障害物左上
			if ((*i)->ID == OBSTACLES_LEFT_UP)
			{
				float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//障害物左上の情報を見ることができる
				float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
				distanceO_L_U -= L;
				if (distanceO_L_U < radius + O_L_U)
				{
					//めり込む量の計算
					float overlap = radius + O_L_U - distanceO_L_U;

					//方向ベクトルを取得して位置を押し戻す
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//正規化する
					direction = Vector_Normalize(direction);
					//ベクトルの長さの設定
					direction = Vector_SetLength(direction, L + 1);

					//押し戻し
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//ベクトルを逆にする
					vec.y *= 1.0;
					break;
				}
			}

			//障害物右上
			else if ((*i)->ID == OBSTACLES_RIGHT_UP)
			{
				float O_R_U = ((CObstacles_RIGHT_UP*)(*i).get())->radius;//障害物右上の情報を見ることができる
				float distanceO_R_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
				distanceO_R_U -= L;
				if (distanceO_R_U < radius + O_R_U)
				{
					//めり込む量の計算
					float overlap = radius + O_R_U - distanceO_R_U;

					//方向ベクトルを取得して位置を押し戻す
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//正規化する
					direction = Vector_Normalize(direction);
					//方向ベクトルの長さ
					float l = Vector_Length(direction);
					//ベクトルの長さの設定
					direction = Vector_SetLength(direction, L + 1.0f);

					//押し戻し
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//ベクトルを逆にする
					vec.y *= 1.0f;
					break;
				}
			}

			//障害物右下
			else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
			{
				float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//障害物右下の情報を見ることができる
				float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める]
				distanceO_R_D -= L;
				if (distanceO_R_D < radius + O_R_D)
				{
					//めり込む量の計算
					float overlap = radius + O_R_D - distanceO_R_D;

					//方向ベクトルを取得して位置を押し戻す
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//正規化する
					direction = Vector_Normalize(direction);

					//方向ベクトルの長さ
					float l = Vector_Length(direction);
					//ベクトルの長さの設定
					direction = Vector_SetLength(direction, L + 1.0f);

					//押し戻し
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//ベクトルを逆にする
					vec.y *= 0.8;
					break;
				}
			}
		}

		//右
		if (pos.x>WINDOW_WIDTH - radius)
		{
			vec.x = -vec.x;
			

			pos.x = WINDOW_WIDTH - radius - 1;


		}

		//左
		if (pos.x < radius)
		{
			vec.x = -vec.x;

			pos.x = radius ;
		}

		//画面の下で跳ね返る
		if (pos.y > WINDOW_HEIGHT - radius  )
		{
			
			
			vec.y = -vec.y;

			pos.y = WINDOW_HEIGHT  - radius - 1;
		}

		//縦
		if (pos.y < radius)
		{
			vec.y = -vec.y;
			pos.y = radius;
		}
		
		
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