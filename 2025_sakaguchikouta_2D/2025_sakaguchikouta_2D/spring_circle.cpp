#pragma once
#include"spring_circle.h"



constexpr auto DAMP{ 0.9f };//減衰率
constexpr auto ACC{ 0.05f };//加速度
constexpr auto C  { 0.7f }; //反発係数
constexpr auto G  { 0.2f }; //重力加速度
constexpr auto EM { 0.008 };//ゴムの弾性定数
constexpr auto SNL{ 0.25f };//ゴムの自然長




Vector move_distance{ 0.0f };//移動速度
int x, y;//マウスの位置

CSpring_Circle::CSpring_Circle()
{
	//ボールの半径
	radius = 32.0f;
	//ボールの初期位置
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;
}

int CSpring_Circle::Action(list<unique_ptr<Base>>& base)
{
	int x, y;
	GetMousePoint(&x, &y);//マウスの位置取得

	//ボールの質量の計算
	M = radius ^ 3;

	//マウスの位置までのベクトルを求める
	move_distance.x = x - pos.x;
	move_distance.y = y - pos.y;

	//ばねの長さ
	move_distance.x -= SNL;
	move_distance.y -= SNL;

	//ゴムの力による加速度
	SA.x = move_distance.x * EM / M;
	SA.y = move_distance.y * EM / M;

	//重力
	W = G * M;
    
	//加速ベクトル
	Vector acc{ 0,0 };
	acc.x =  ACC * move_distance.x + SA.x;
	acc.y =  ACC * move_distance.y + W  + SA.y;
	


	//移動ベクトル
	vec.x =  DAMP * (vec.x + acc.x );
	vec.y =  DAMP * (vec.y + acc.y );
    

	//座標更新
	pos.x += vec.x;
	pos.y += vec.y;

	//画面左の跳ね返り
	if (pos.x < radius)
	{
		pos.x = radius;
		vec.x *= C;
		vec.x = -vec.x;
	}
	//画面右の跳ね返り
	if (pos.x >  WINDOW_WIDTH - radius)
	{
		vec.x *= C;
		vec.x = -vec.x;
		pos.x = WINDOW_WIDTH - radius - 1;
	}
	//画面下の跳ね返り
	if (pos.y > WINDOW_HEIGHT- radius)
	{
		vec.y *= C;
		vec.y = -vec.y ;
		pos.y = WINDOW_HEIGHT - radius - 1;
	}
	//画面上の跳ね返り
	if(pos.y < radius)
	{ 
		pos.y = radius;
		vec.y *= C;
		vec.y = -vec.y;
	}
			

	return 0;
}

void CSpring_Circle::Draw()
{
	GetMousePoint(&x, &y);//マウスの位置取得
	//ばねの始点
	DrawCircle(x, y, radius / 2, GetColor(255, 255, 255), false);
	//ばね
	DrawLine( x, y, pos.x, pos.y, GetColor(255, 0, 0), 1);
	//ばねの終点にボール
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);
}