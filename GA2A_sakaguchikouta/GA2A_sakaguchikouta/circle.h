//circle.h
#pragma once
#include"objBase.h"

class CCircle : public Base
{
public:
	CCircle();
	CCircle(int x, int y);

	//���a
	int radius;
	int clear_to_frame;

	int Action(list<unique_ptr<Base>>&);
	void Draw();

	

	bool vanish = true;
};
