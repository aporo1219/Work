#include "Box.h"


Box::Box()
{
	pos.x = 100;
	pos.y = 100;

	//ID‚Ì‘ã“ü
	ID = BOX;
}

int Box::Action(list<unique_ptr<Base>>& base)
{
	return 0;
}

void Box::Draw()
{
	LoadGraphScreen(pos.x, pos.y, "Image\\box.png", TRUE);
}

