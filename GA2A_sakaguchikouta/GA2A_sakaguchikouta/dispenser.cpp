//dispenser.cpp

#include"dispenser.h"
#include"function.h"

CDispenser::CDispenser(int x, int y)
{
	x = 400;
	y = 550;
	//‰Šú’l
	pos.x = x;
	pos.y = y;

	ID = Dispenser;
}

int CDispenser::Action(list<unique_ptr<Base>>& base)
{
	return 0;
}

void CDispenser::Draw()
{
	DrawBox(380, 550, 420, 600, GetColor(255, 255, 255), true);
}