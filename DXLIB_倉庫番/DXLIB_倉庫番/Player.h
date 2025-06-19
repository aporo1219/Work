#pragma once
#include"objBase.h"

class Player : public Base
{
public:
	Player();

	int Action(list<unique_ptr<Base>>&);

	void Draw();
};