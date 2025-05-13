#pragma once
//obstacles.h
#include"objBase.h"

//ç∂è„
class CObstacles_LEFT_UP : public Base
{
public:
	CObstacles_LEFT_UP(int x, int y);

	//îºåa
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};

//âEè„
class CObstacles_RIGHT_UP : public Base
{
public:
	CObstacles_RIGHT_UP(int x, int y);

	//îºåa
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};

//âEâ∫
class CObstacles_RIGHT_DOWN : public Base
{
public:
	CObstacles_RIGHT_DOWN(int x, int y);

	//îºåa
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};
