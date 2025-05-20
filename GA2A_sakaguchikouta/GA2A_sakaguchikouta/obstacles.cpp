//obstaches.cpp
#include"obstacles.h"
#include"function.h"


//左上
CObstacles_LEFT_UP::CObstacles_LEFT_UP(int x, int y)
{
	//初期位置
	pos.x = 50;
	pos.y = 100;

	radius = 40.0;

	ID = OBSTACLES_LEFT_UP;
}

int CObstacles_LEFT_UP::Action(list<unique_ptr<Base>>& base)
{

	return 0;
}

void CObstacles_LEFT_UP::Draw()
{
	DrawCircle(pos.x,pos.y,radius,GetColor(0, 0, 255), true);
}



//右上
CObstacles_RIGHT_UP::CObstacles_RIGHT_UP(int x, int y)
{
	//初期位置
	pos.x = 720;
	pos.y = 250;

	radius = 40.0;

	ID = OBSTACLES_RIGHT_UP;
}

int CObstacles_RIGHT_UP::Action(list<unique_ptr<Base>>& base)
{


	return 0;
}

void CObstacles_RIGHT_UP::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 0), true);
}



//右下
CObstacles_RIGHT_DOWN::CObstacles_RIGHT_DOWN(int x, int y)
{
	//初期位置
	pos.x = 720;
	pos.y = 500;

	radius = 40.0;

	ID = OBSTACLES_RIGHT_DOWN;
}

int CObstacles_RIGHT_DOWN::Action(list<unique_ptr<Base>>& base)
{


	return 0;
}

void CObstacles_RIGHT_DOWN::Draw()
{
	DrawCircle(pos.x, pos.y,radius, GetColor(255, 0, 0), true);
}
