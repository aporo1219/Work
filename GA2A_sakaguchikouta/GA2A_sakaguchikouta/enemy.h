#pragma once
//enemy.h
#include"objBase.h"

class CEnemy : public Base
{
public:
	CEnemy(int x, int y);

	//���a
	int radius;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

};
