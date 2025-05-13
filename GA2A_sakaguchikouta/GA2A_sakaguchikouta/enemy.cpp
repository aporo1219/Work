//enemy.cpp
#include"enemy.h"
#include"function.h"
#include"obstacles.h"

//�d�͉����x
constexpr auto g = 0.98f;

CEnemy::CEnemy(int x, int y)
{
	radius = 32.0f;

	//�����ʒu
	pos.x = x;
	pos.y = y;

	vec.x = 0.2f;
	vec.y = 0.5f;

	vec = Vector_SetLength(vec, 30.0f);

	ID = ENEMY;
}

int CEnemy::Action(list<unique_ptr<Base>>& base)
{
	
	pos.x += vec.x;
	pos.y += vec.y;

	for (auto i = base.begin();i != base.end();i++)
	{


		//��Q������
		if ((*i)->ID == OBSTACLES_LEFT_UP)
		{
			float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//��Q������̏������邱�Ƃ��ł���
			float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
			if (distanceO_L_U < radius + O_L_U)
			{
				vec.y = -vec.y;//�x�N�g�����t�ɂ���
				vec.y += 5.0;
				break;
			}
		}

		//��Q���E��
		else if ((*i)->ID == OBSTACLES_RIGHT_UP)
		{
			float O_R_U = ((CObstacles_RIGHT_UP*)(*i).get())->radius;//��Q���E��̏������邱�Ƃ��ł���
			float distanceO_R_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
			if (distanceO_R_U < radius + O_R_U)
			{
				vec.y = -vec.y;//�x�N�g�����t�ɂ���
				vec.y += 5.0;
				break;
			}
		}

		//��Q���E��
		else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
		{
			float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//��Q���E���̏������邱�Ƃ��ł���
			float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
			if (distanceO_R_D < radius + O_R_D)
			{
				
				vec.y = -vec.y;//�x�N�g�����t�ɂ���
				vec.y += 5.0;
				break;
			}
		}
	}

	if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
	{
		vec.x = -vec.x;
		
	}

	//��ʂ̉��Œ��˕Ԃ�
	if (pos.y > WINDOW_HEIGHT - radius||pos.y<radius)
	{
		vec.y = -vec.y;//�x�N�g�����t�ɂ���
	}

	return 0;
}

void CEnemy::Draw()
{
	DrawCircle(
		pos.x, pos.y,          //���S���W
		radius,               //���a
		GetColor(255, 0, 0),//�F
		false               //�h��Ԃ�(false/true)
	);

}