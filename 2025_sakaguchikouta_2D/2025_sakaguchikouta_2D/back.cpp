#pragma once
#include"back.h"

Cback::Cback()
{
	pos.x = 0;
	pos.y = 0;
}

int Cback::Action(list<unique_ptr<Base>>& base)
{
	return 0;
}

void Cback::Draw()
{
	LoadGraphScreen(pos.x, pos.y, "image\\house.jpg", TRUE);
}