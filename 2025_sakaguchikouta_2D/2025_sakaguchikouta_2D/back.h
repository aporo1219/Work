#pragma once
#include"objBase.h"

class Cback :public Base
{
public:
	Cback();

	int Action(list<unique_ptr<Base>>&);
	void Draw();
};