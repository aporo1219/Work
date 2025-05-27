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

	vec = Vector_SetLength(vec, 10.0f);

	ID = ENEMY;
	Vector_Normalize(vec);

}

int CEnemy::Action(list<unique_ptr<Base>>& base)
{
	if (GLIFE > 0)
	{
		float L = 0.0f;
		pos.x += vec.x;
		pos.y += vec.y;

		L = Vector_Length(vec);

		for (auto i = base.begin();i != base.end();i++)
		{


			//��Q������
			if ((*i)->ID == OBSTACLES_LEFT_UP)
			{
				float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//��Q������̏������邱�Ƃ��ł���
				float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
				distanceO_L_U -= L;
				if (distanceO_L_U < radius + O_L_U)
				{
					//�߂荞�ޗʂ̌v�Z
					float overlap = radius + O_L_U - distanceO_L_U;

					//�����x�N�g�����擾���Ĉʒu�������߂�
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//���K������
					direction = Vector_Normalize(direction);
					//�x�N�g���̒����̐ݒ�
					direction = Vector_SetLength(direction, L + 1);

					//�����߂�
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//�x�N�g�����t�ɂ���
					vec.y *= 1.0;
					break;
				}
			}

			//��Q���E��
			else if ((*i)->ID == OBSTACLES_RIGHT_UP)
			{
				float O_R_U = ((CObstacles_RIGHT_UP*)(*i).get())->radius;//��Q���E��̏������邱�Ƃ��ł���
				float distanceO_R_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
				distanceO_R_U -= L;
				if (distanceO_R_U < radius + O_R_U)
				{
					//�߂荞�ޗʂ̌v�Z
					float overlap = radius + O_R_U - distanceO_R_U;

					//�����x�N�g�����擾���Ĉʒu�������߂�
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//���K������
					direction = Vector_Normalize(direction);
					//�����x�N�g���̒���
					float l = Vector_Length(direction);
					//�x�N�g���̒����̐ݒ�
					direction = Vector_SetLength(direction, L + 1.0f);

					//�����߂�
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//�x�N�g�����t�ɂ���
					vec.y *= 1.0f;
					break;
				}
			}

			//��Q���E��
			else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
			{
				float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//��Q���E���̏������邱�Ƃ��ł���
				float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�]
				distanceO_R_D -= L;
				if (distanceO_R_D < radius + O_R_D)
				{
					//�߂荞�ޗʂ̌v�Z
					float overlap = radius + O_R_D - distanceO_R_D;

					//�����x�N�g�����擾���Ĉʒu�������߂�
					Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
					//���K������
					direction = Vector_Normalize(direction);

					//�����x�N�g���̒���
					float l = Vector_Length(direction);
					//�x�N�g���̒����̐ݒ�
					direction = Vector_SetLength(direction, L + 1.0f);

					//�����߂�
					pos.x += direction.x * overlap;
					pos.y += direction.y * overlap;

					vec.y = -vec.y;//�x�N�g�����t�ɂ���
					vec.y *= 0.8;
					break;
				}
			}
		}

		//�E
		if (pos.x>WINDOW_WIDTH - radius)
		{
			vec.x = -vec.x;
			

			pos.x = WINDOW_WIDTH - radius - 1;


		}

		//��
		if (pos.x < radius)
		{
			vec.x = -vec.x;

			pos.x = radius ;
		}

		//��ʂ̉��Œ��˕Ԃ�
		if (pos.y > WINDOW_HEIGHT - radius  )
		{
			
			
			vec.y = -vec.y;

			pos.y = WINDOW_HEIGHT  - radius - 1;
		}

		//�c
		if (pos.y < radius)
		{
			vec.y = -vec.y;
			pos.y = radius;
		}
		
		
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