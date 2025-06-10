#pragma once
#include"spring_circle.h"



constexpr auto DAMP{ 0.9f };//������
constexpr auto ACC{ 0.05f };//�����x
constexpr auto C  { 0.7f }; //�����W��
constexpr auto G  { 0.2f }; //�d�͉����x
constexpr auto EM { 0.008 };//�S���̒e���萔
constexpr auto SNL{ 0.25f };//�S���̎��R��




Vector move_distance{ 0.0f };//�ړ����x
int x, y;//�}�E�X�̈ʒu

CSpring_Circle::CSpring_Circle()
{
	//�{�[���̔��a
	radius = 32.0f;
	//�{�[���̏����ʒu
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;
}

int CSpring_Circle::Action(list<unique_ptr<Base>>& base)
{
	int x, y;
	GetMousePoint(&x, &y);//�}�E�X�̈ʒu�擾

	//�{�[���̎��ʂ̌v�Z
	M = radius ^ 3;

	//�}�E�X�̈ʒu�܂ł̃x�N�g�������߂�
	move_distance.x = x - pos.x;
	move_distance.y = y - pos.y;

	//�΂˂̒���
	move_distance.x -= SNL;
	move_distance.y -= SNL;

	//�S���̗͂ɂ������x
	SA.x = move_distance.x * EM / M;
	SA.y = move_distance.y * EM / M;

	//�d��
	W = G * M;
    
	//�����x�N�g��
	Vector acc{ 0,0 };
	acc.x =  ACC * move_distance.x + SA.x;
	acc.y =  ACC * move_distance.y + W  + SA.y;
	


	//�ړ��x�N�g��
	vec.x =  DAMP * (vec.x + acc.x );
	vec.y =  DAMP * (vec.y + acc.y );
    

	//���W�X�V
	pos.x += vec.x;
	pos.y += vec.y;

	//��ʍ��̒��˕Ԃ�
	if (pos.x < radius)
	{
		pos.x = radius;
		vec.x *= C;
		vec.x = -vec.x;
	}
	//��ʉE�̒��˕Ԃ�
	if (pos.x >  WINDOW_WIDTH - radius)
	{
		vec.x *= C;
		vec.x = -vec.x;
		pos.x = WINDOW_WIDTH - radius - 1;
	}
	//��ʉ��̒��˕Ԃ�
	if (pos.y > WINDOW_HEIGHT- radius)
	{
		vec.y *= C;
		vec.y = -vec.y ;
		pos.y = WINDOW_HEIGHT - radius - 1;
	}
	//��ʏ�̒��˕Ԃ�
	if(pos.y < radius)
	{ 
		pos.y = radius;
		vec.y *= C;
		vec.y = -vec.y;
	}
			

	return 0;
}

void CSpring_Circle::Draw()
{
	GetMousePoint(&x, &y);//�}�E�X�̈ʒu�擾
	//�΂˂̎n�_
	DrawCircle(x, y, radius / 2, GetColor(255, 255, 255), false);
	//�΂�
	DrawLine( x, y, pos.x, pos.y, GetColor(255, 0, 0), 1);
	//�΂˂̏I�_�Ƀ{�[��
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), true);
}