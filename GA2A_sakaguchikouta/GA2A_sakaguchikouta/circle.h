//circle.h
#pragma once
#include"objBase.h"

class CCircle : public Base
{
public:
	CCircle();
	CCircle(int x, int y);

	//”¼Œa
	int radius;
	

	int Action(list<unique_ptr<Base>>&);
	void Draw();

	bool vanish = true;
};
