#pragma once
#include"objBase.h"

class CSpring_Circle :public Base
{
public:
	CSpring_Circle();

	int radius;
	float M = 0.0f;//����
	float W = 0;//�d��
	Vector SL{ 0 ,0};//�΂˂̒���
	Vector F{ 0,0 };//�΂˂̔���
	Vector SA = { 0,0 };//�S������̗͂ɂ������x

	int Action(list<unique_ptr<Base>>&);
	void Draw();

	
};