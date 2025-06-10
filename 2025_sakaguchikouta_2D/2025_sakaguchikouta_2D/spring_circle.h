#pragma once
#include"objBase.h"

class CSpring_Circle :public Base
{
public:
	CSpring_Circle();

	int radius;
	float M = 0.0f;//¿—Ê
	float W = 0;//d—Í
	Vector SL{ 0 ,0};//‚Î‚Ë‚Ì’·‚³
	Vector F{ 0,0 };//‚Î‚Ë‚Ì”½”­
	Vector SA = { 0,0 };//ƒSƒ€‚©‚ç‚Ì—Í‚É‚æ‚é‰Á‘¬“x

	int Action(list<unique_ptr<Base>>&);
	void Draw();

	
};