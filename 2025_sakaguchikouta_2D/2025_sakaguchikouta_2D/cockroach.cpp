#pragma once
#include"cockroach.h"

CCockroach::CCockroach()
{
	pos.x = 0;
	pos.y = RandPos();
}

int CCockroach::Action(list<unique_ptr<Base>>& base)
{

	vec.x += SG;
	pos.x += vec.x;
	//�ʒu���E��ʒ[�܂ōs���ƍ��Ƀ��[�v
	if (pos.x > WINDOW_WIDTH)
	{
		pos.x = 0;
		pos.y = RandPos();
		vec.x = 0;
	}

	return 0;
}

void CCockroach::Draw()
{
	LoadGraphScreen(pos.x, pos.y, "image\\G1.png", TRUE);
}

//�����l�̃����_���֐�
int CCockroach::RandPos()
{
	int  rand_y = 0;
	rand_y = GetRand(600);//y�����̏��������_��
	return rand_y;
}