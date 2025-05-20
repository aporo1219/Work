#pragma once
//dispencer.h

#include"objBase.h"

class CDispenser : public Base
{
public:
	CDispenser(int x, int y);


   int Action(list<unique_ptr<Base>>&);
	void Draw();
};
