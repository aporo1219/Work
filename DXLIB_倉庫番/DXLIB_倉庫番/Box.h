#pragma once
#include"objBase.h"

class Box : public Base
{
public:
	Box();

	int Action(list<unique_ptr<Base>>&);

	void Draw();
};