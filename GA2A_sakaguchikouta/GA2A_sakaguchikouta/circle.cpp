//circle.cpp
#include"circle.h"
#include"function.h"
#include"enemy.h"
#include"obstacles.h"

//�d�͉����x
constexpr auto g = 0.98f;

CCircle::CCircle()
{
	radius = 32.0f;

	pos.x = 100.0f;
	pos.y = WINDOW_HEIGHT / 2;

}

CCircle::CCircle(int x, int y)
{
	radius = 32.0f;

	//�����ʒu
	//pos.x = x;
	//pos.y = y;
	pos.x = radius;
	pos.y = WINDOW_HEIGHT - radius;


	//vec.x = 4.0f;

	//�N���b�N���������̃x�N�g�������߂�
	vec.x = x - pos.x;
	vec.y = y - pos.y;

	vec = Vector_SetLength(vec, 30.0f);


	
}

int CCircle::Action(list<unique_ptr<Base>>& base)
{
	vec.y += g;

	pos.x += vec.x;
	pos.y += vec.y;

	//�����蔻��
	{
		for (auto i = base.begin();i != base.end();i++)
		{
			//�G
			if ((*i)->ID == ENEMY)
			{
				float e_radius = ((CEnemy*)(*i).get())->radius;//�G�̏������邱�Ƃ��ł���
				float distance = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
				if (distance < radius + e_radius)
				{
					//�������Ă���
					//GSCORE++;
					FLAG = false;
					vec.y = -vec.y;//�x�N�g�����t�ɂ���
					vec.y *= 0.8;//����
					break;
				}
			}

			//��Q������
			else if ((*i)->ID == OBSTACLES_LEFT_UP)
			{
				float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//��Q������̏������邱�Ƃ��ł���
				float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
				if (distanceO_L_U < radius +O_L_U)
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
					
					GSCORE--;
					vec.y = -vec.y;//�x�N�g�����t�ɂ���
					vec.y += 5.0;
					break;
				}
			}
		}
	}

	//��ʉ��Œ��˕Ԃ�
	if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
	{
		vec.x = -vec.x;
	}

	//��ʂ̉��Œ��˕Ԃ�
	if (pos.y > WINDOW_HEIGHT - radius)
	{
		
		pos.y = WINDOW_HEIGHT - radius - 1;//-1�́A����
		vec.y = -vec.y;//�x�N�g�����t�ɂ���
		//vec.y *= 0.8;
	}
	
	//��ʂ̊O�ɂł��������
	//if (pos.y > WINDOW_HEIGHT + radius * 2) FLAG = false;

	//���Ԃ��o�߂���Ɖ~�̍폜
	clear_to_frame++;
	//if (clear_to_frame == 120)
	//FLAG = false;//120f�ō폜

	return 0;
}

void CCircle::Draw()
{
	DrawCircle(
		pos.x, pos.y,          //���S���W
		radius,               //���a
		GetColor(255, 255, 255),//�F
		false                //�h��Ԃ�faslse/true
	);

}