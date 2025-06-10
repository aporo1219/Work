#pragma once
#include"objBase.h"

class CCockroach :public Base
{
public:
	CCockroach();

	float SG = 0.1f;
	int Action(list<unique_ptr<Base>>&);
	int Action1(list<unique_ptr<Base>>&);
	int Action2(list<unique_ptr<Base>>&);
	int Action3(list<unique_ptr<Base>>&);
	void Draw();
	int RandPos();
};

