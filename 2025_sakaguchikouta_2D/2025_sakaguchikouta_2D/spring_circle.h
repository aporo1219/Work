#pragma once
#include"objBase.h"

class CSpring_Circle :public Base
{
public:
	CSpring_Circle();

	int radius;
	float M = 0.0f;//質量
	float W = 0;//重力
	Vector SL{ 0 ,0};//ばねの長さ
	Vector F{ 0,0 };//ばねの反発
	Vector SA = { 0,0 };//ゴムからの力による加速度

	int Action(list<unique_ptr<Base>>&);
	void Draw();

	
};