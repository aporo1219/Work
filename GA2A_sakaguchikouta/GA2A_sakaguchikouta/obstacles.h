#pragma once
//obstacles.h
#include"objBase.h"

//����
class CObstacles_LEFT_UP : public Base
{
public:
	CObstacles_LEFT_UP(int x, int y);

	//���a
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};

//�E��
class CObstacles_RIGHT_UP : public Base
{
public:
	CObstacles_RIGHT_UP(int x, int y);

	//���a
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};

//�E��
class CObstacles_RIGHT_DOWN : public Base
{
public:
	CObstacles_RIGHT_DOWN(int x, int y);

	//���a
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};
