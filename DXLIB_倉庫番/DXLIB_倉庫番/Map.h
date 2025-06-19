#pragma once
#include "objBase.h"

class Map : public Base
{
public:
	Map();

	int Action(list<unique_ptr<Base>>&);

	void Draw();
};

void MapDraw();

