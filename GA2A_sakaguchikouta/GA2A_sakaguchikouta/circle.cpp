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

	pos.x = 400.0f;
	pos.y = WINDOW_HEIGHT / 2;

}

CCircle::CCircle(int x, int y)
{
	
	radius = 32.0f;

	//初期位置
	//pos.x = x;
	//pos.y = y;
	pos.x = 400.0f;
	pos.y = WINDOW_HEIGHT - radius;


	//vec.x = 4.0f;

	//クリックした方向のベクトルを求める
	vec.x = x - pos.x;
	vec.y = y - pos.y;

	vec = Vector_SetLength(vec, 25.0f);

	Vector_Normalize(vec);
	
}

int CCircle::Action(list<unique_ptr<Base>>& base)
{
	if (GLIFE > 0)
	{
		float L = 0.0f;

		vec.y += g;

		pos.x += vec.x;
		pos.y += vec.y;

		L = Vector_Length(vec);

		//当たり判定
		{
			for (auto i = base.begin();i != base.end();i++)
			{
				//敵
				if ((*i)->ID == ENEMY)
				{
					float e_radius = ((CEnemy*)(*i).get())->radius;//敵の情報を見ることができる
					float distance = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
					distance -= L;
					if (distance < radius + e_radius)
					{
						//めり込む量の計算
						float overlap = radius + e_radius - distance;

						//方向ベクトルを取得して位置を押し戻す
						Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
						//正規化する
						direction = Vector_Normalize(direction);

						//押し戻し
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;

						//当たっている
						GSCORE++;
						FLAG = false;
						if (FLAG == false)
						{
							VANISH = true;
						}
						break;
					}
				}

				//障害物左上
				//ライフの回復
				else if ((*i)->ID == OBSTACLES_LEFT_UP)
				{
					float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//障害物左上の情報を見ることができる
					float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
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


						GLIFE++;
						if (FLAG == false)
						{
							
							VANISH = true;
						}
						break;
					}
				}

				//障害物右上
				//反発力が高い
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
						//ベクトルの長さの設定
						direction = Vector_SetLength(direction, L + 1);

						//押し戻し
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;
                        vec.y *= 1.1;

						vec.y = -vec.y;//ベクトルを逆にする
						vec.y = radius - 0.5;
						
						break;
					}
				}

				//障害物右下
				//スコアの減少
				else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
				{
					float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//障害物右下の情報を見ることができる
					float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2点間距離を求める
					if (distanceO_R_D < radius + O_R_D)
					{
						//めり込む量の計算
						float overlap = radius + O_R_D - distanceO_R_D;

						//方向ベクトルを取得して位置を押し戻す
						Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
						//正規化する
						direction = Vector_Normalize(direction);

						//押し戻し
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;

						GSCORE--;
						FLAG = false;
						GLIFE--;
						
						if (FLAG == false)
						{
							
							VANISH = true;
						}
						break;
					}
				}
			}
		}

		//画面横で跳ね返る
		if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
		{
			vec.x = -vec.x;
			vec.x *= 1.0;
		}

		//画面の下で跳ね返る
		if (pos.y > WINDOW_HEIGHT - radius)
		{

			pos.y = WINDOW_HEIGHT - radius - 1;//-1は、線幅
            
			vec.y = -vec.y;//ベクトルを逆にする

			vec.y *= 1.0;
		}

	    //画面の外にでたら消える
		if (pos.y > WINDOW_HEIGHT + radius * 2)
		{
          FLAG = false;
		  if (FLAG == false)
		  {
			  
			  VANISH = true;
		  }
		}
			

		//時間が経過すると円の削除

		if (clear_to_frame == 120)
		FLAG = false;
		if (FLAG == false)
		{
			VANISH = true;
		}//120fで削除
	}
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

