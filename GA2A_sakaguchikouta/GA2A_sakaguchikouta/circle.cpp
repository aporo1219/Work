//circle.cpp
#include"circle.h"
#include"function.h"
#include"enemy.h"
#include"obstacles.h"

//重力加速度
constexpr auto g = 0.98f;

CCircle::CCircle()
{
	radius = 32.0f;

	pos.x = 100.0f;
	pos.y = WINDOW_HEIGHT / 2;

}

CCircle::CCircle(int x, int y)
{
	radius = 32.0f;

	//初期位置
	//pos.x = x;
	//pos.y = y;
	pos.x = radius;
	pos.y = WINDOW_HEIGHT - radius;


	//vec.x = 4.0f;

	//クリックした方向のベクトルを求める
	vec.x = x - pos.x;
	vec.y = y - pos.y;

	vec = Vector_SetLength(vec, 30.0f);


	
}

int CCircle::Action(list<unique_ptr<Base>>& base)
{
	vec.y += g;

	pos.x += vec.x;
	pos.y += vec.y;

	//当たり判定
	{
		for (auto i = base.begin();i != base.end();i++)
		{
			//敵
			if ((*i)->ID == ENEMY)
			{
				float e_radius = ((CEnemy*)(*i).get())->radius;//敵の情報を見ることができる
				float distance = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
				if (distance < radius + e_radius)
				{
					//当たっている
					//GSCORE++;
					FLAG = false;
					vec.y = -vec.y;//ベクトルを逆にする
					vec.y *= 0.8;//反発
					break;
				}
			}

			//障害物左上
			else if ((*i)->ID == OBSTACLES_LEFT_UP)
			{
				float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//障害物左上の情報を見ることができる
				float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
				if (distanceO_L_U < radius +O_L_U)
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
					
					GSCORE--;
					vec.y = -vec.y;//ベクトルを逆にする
					vec.y += 5.0;
					break;
				}
			}
		}
	}

	//画面横で跳ね返る
	if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
	{
		vec.x = -vec.x;
	}

	//画面の下で跳ね返る
	if (pos.y > WINDOW_HEIGHT - radius)
	{
		
		pos.y = WINDOW_HEIGHT - radius - 1;//-1は、線幅
		vec.y = -vec.y;//ベクトルを逆にする
		//vec.y *= 0.8;
	}
	
	//画面の外にでたら消える
	//if (pos.y > WINDOW_HEIGHT + radius * 2) FLAG = false;

	//時間が経過すると円の削除
	clear_to_frame++;
	//if (clear_to_frame == 120)
	//FLAG = false;//120fで削除

	return 0;
}

void CCircle::Draw()
{
	DrawCircle(
		pos.x, pos.y,          //中心座標
		radius,               //半径
		GetColor(255, 255, 255),//色
		false                //塗りつぶしfaslse/true
	);

}