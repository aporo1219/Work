#include"stdio.h"
#define X 8      
#define Y 8


int PlayerX = 1, PlayerY = 1;
int map[Y][X] =
{1,1,1,1,1,1,1,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,1,1,1,1,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1 };

int Box_X = 5,Box_Y = 2;//���̕ϐ�
int Goal_X = 5, Goal_Y = 5;//�S�[���ʒu�̕ϐ�


void Move();
void Win();
void Box(int bm);
int Lose();

int main(void)
{
	PlayerX = 1, PlayerY = 1;

	int i, j;

    

	//�}�b�v����
	for (i = 0; i < Y; i++)
	{
		for (j = 0; j < X; j++)
		{
			if (map[i][j] == 1)
			{
				printf("��");
			}
			else if (i == PlayerY && j == PlayerX)
			{
				printf("�o");
				
			}
			else if (i==Box_Y && j == Box_X)
			{
				printf("��");
			}
			else if (i == Goal_Y && j == Goal_X)
			{
				printf("�E");
			}
			else
			{
				printf("  ");

			}
		}
		printf("\n");
	}

	//�e�L�X�g�̕\��
	printf("�ړ����������(�e���L�[�\������)\n");
	printf("��:4 �E:6 ��:8 ��:2\n");

	

	while (1)
	{
		Move();
		
		
		for (i = 0; i < Y; i++)
		{
			for (j = 0; j < X; j++)
			{

				
				//���͌�̕\��
				if (map[i][j] == 1)
				{
					printf("��");
				}
				//�v���C���[�̌��ݒn�̕\��
				else if (PlayerY == i && PlayerX == j )
				{
					printf("�o");
				}
				//���̈ʒu
				else if (Box_Y == i && Box_X == j)
				{
					printf("��");
				}
				//�S�[���̈ʒu
				else if (Goal_Y == i && Goal_X == j)
				{
					printf("�E");
					map[Goal_Y][Goal_X] = 4;
				}
				else
				{
					printf("  ");
				}


			}
			printf("\n");



		}

		//�Q�[���̃N���A�����̃`�F�b�N
		if ( 4 == map[Box_Y][Box_X])
		{
			Win();
			break;
		}

		//�Q�[���̃I�[�o�����̃`�F�b�N
		if (!Lose())
		{
			printf("�Q�[���I�[�o�[\n");
			break;
		}
		//�e�L�X�g�̕\��
		printf("�ړ����������(�e���L�[�\������)\n");
		printf("��:4 �E:6 ��:8 ��:2\n");

	}

	return 0;
}

//�v���C���[�̈ړ��̊֐�
void Move()
{
	int key = 0;

	int Box_Move = 0;

	scanf_s("%d", &key);

	//��
	if (key == 4 && map[PlayerY][PlayerX - 1] == 0)
	{
        PlayerX--;
		if (map[PlayerY][PlayerX - 1] == 2)
		{
			printf("��");
		}
	}
	//�E
	else if (key == 6 && map[PlayerY][PlayerX + 1] == 0 )
	{
       PlayerX++;
	  
	   //�E�Ƀv���C���[������A�E�ɓ��͂��ꂽ��A�����i�����ɕǂ��Ȃ������甠���i��
	 
	   Box_Move = 6;
	   Box(Box_Move);
	}
		

	//��
	else if (key == 8 && map[PlayerY - 1][PlayerX] == 0)
	{
      PlayerY--;

	  //��Ƀv���C���[������A��ɓ��͂��ꂽ��A�����i�����ɕǂ��Ȃ������甠���i��
	  /*if (map[PlayerY - 1][PlayerX] == map[Box_Y][Box_X])
	  {
		  Box_Move = 8;
		  Box(Box_Move);
	  }*/
	}
		

	//��
	else if (key == 2 && map[PlayerY + 1][PlayerX] == 0)
	{
       PlayerY++;

	   //���Ƀv���C���[������A���ɓ��͂��ꂽ��A�����i�����ɕǂ��Ȃ��Ȃ����甠���i��
		   Box_Move = 2;
		   Box(Box_Move);
	   
	}
		

}

//���ړ��̊֐�
void Box(int bm)
{
	switch (bm)
	{
	case 4:
		//���Ƀv���C���[������A������͂��ꂽ��A�����i�ޕ����ɕǂ��Ȃ������甠���i��
		if (map[Box_Y][Box_X - 1] == 0)
		{
           Box_X--;
		}
	case 2:
		if (map[Box_Y + 1][Box_X] == 0)
		{
			Box_Y++;
		}
	}
}

//�Q�[���N���A�̊֐�
void Win()
{
	printf("�N���A\n");
}

//�Q�[���I�[�o�[�̊֐�
int Lose()
{
	//�����0(�i�߂�j�}�X���m���߂�
	if (map[PlayerY][PlayerX + 1] == 0 || map[PlayerY][PlayerX - 1] == 0 || map[PlayerY - 1][PlayerX] == 0 || map[PlayerY + 1][PlayerX] == 0)
	{
		return 1;
	}
	return 0;
}