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

	pos.x = 400.0f;
	pos.y = WINDOW_HEIGHT / 2;

}

CCircle::CCircle(int x, int y)
{
	
	radius = 32.0f;

	//�����ʒu
	//pos.x = x;
	//pos.y = y;
	pos.x = 400.0f;
	pos.y = WINDOW_HEIGHT - radius;


	//vec.x = 4.0f;

	//�N���b�N���������̃x�N�g�������߂�
	vec.x = x - pos.x;
	vec.y = y - pos.y;

	vec = Vector_SetLength(vec, 25.0f);

	Vector_Normalize(vec);
	
}

int CCircle::Action(list<unique_ptr<Base>>& base)
{
	if (GLIFE > 0)
	{
		float L = 0.0f;

		vec.y += g;

		pos.x += vec.x;
		pos.y += vec.y;

		L = Vector_Length(vec);

		//�����蔻��
		{
			for (auto i = base.begin();i != base.end();i++)
			{
				//�G
				if ((*i)->ID == ENEMY)
				{
					float e_radius = ((CEnemy*)(*i).get())->radius;//�G�̏������邱�Ƃ��ł���
					float distance = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
					distance -= L;
					if (distance < radius + e_radius)
					{
						//�߂荞�ޗʂ̌v�Z
						float overlap = radius + e_radius - distance;

						//�����x�N�g�����擾���Ĉʒu�������߂�
						Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
						//���K������
						direction = Vector_Normalize(direction);

						//�����߂�
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;

						//�������Ă���
						GSCORE++;
						FLAG = false;
						if (FLAG == false)
						{
							VANISH = true;
						}
						break;
					}
				}

				//��Q������
				//���C�t�̉�
				else if ((*i)->ID == OBSTACLES_LEFT_UP)
				{
					float O_L_U = ((CObstacles_LEFT_UP*)(*i).get())->radius;//��Q������̏������邱�Ƃ��ł���
					float distanceO_L_U = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
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


						GLIFE++;
						if (FLAG == false)
						{
							
							VANISH = true;
						}
						break;
					}
				}

				//��Q���E��
				//�����͂�����
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
						//�x�N�g���̒����̐ݒ�
						direction = Vector_SetLength(direction, L + 1);

						//�����߂�
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;
                        vec.y *= 1.1;

						vec.y = -vec.y;//�x�N�g�����t�ɂ���
						vec.y = radius - 0.5;
						
						break;
					}
				}

				//��Q���E��
				//�X�R�A�̌���
				else if ((*i)->ID == OBSTACLES_RIGHT_DOWN)
				{
					float O_R_D = ((CObstacles_RIGHT_DOWN*)(*i).get())->radius;//��Q���E���̏������邱�Ƃ��ł���
					float distanceO_R_D = DistanceF(pos.x, pos.y, (*i)->pos.x, (*i)->pos.y);//2�_�ԋ��������߂�
					if (distanceO_R_D < radius + O_R_D)
					{
						//�߂荞�ޗʂ̌v�Z
						float overlap = radius + O_R_D - distanceO_R_D;

						//�����x�N�g�����擾���Ĉʒu�������߂�
						Vector direction = { pos.x - (*i)->pos.x,pos.y - (*i)->pos.y };
						//���K������
						direction = Vector_Normalize(direction);

						//�����߂�
						pos.x += direction.x * overlap;
						pos.y += direction.y * overlap;

						GSCORE--;
						FLAG = false;
						GLIFE--;
						
						if (FLAG == false)
						{
							
							VANISH = true;
						}
						break;
					}
				}
			}
		}

		//��ʉ��Œ��˕Ԃ�
		if (pos.x<radius || pos.x>WINDOW_WIDTH - radius)
		{
			vec.x = -vec.x;
			vec.x *= 1.0;
		}

		//��ʂ̉��Œ��˕Ԃ�
		if (pos.y > WINDOW_HEIGHT - radius)
		{

			pos.y = WINDOW_HEIGHT - radius - 1;//-1�́A����
            
			vec.y = -vec.y;//�x�N�g�����t�ɂ���

			vec.y *= 1.0;
		}

	    //��ʂ̊O�ɂł��������
		if (pos.y > WINDOW_HEIGHT + radius * 2)
		{
          FLAG = false;
		  if (FLAG == false)
		  {
			  
			  VANISH = true;
		  }
		}
			

		//���Ԃ��o�߂���Ɖ~�̍폜

		if (clear_to_frame == 120)
		FLAG = false;
		if (FLAG == false)
		{
			VANISH = true;
		}//120f�ō폜
	}
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

