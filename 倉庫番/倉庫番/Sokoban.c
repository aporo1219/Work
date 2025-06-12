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

int Box_X = 5,Box_Y = 2;//箱の変数
int Goal_X = 5, Goal_Y = 5;//ゴール位置の変数


void Move();
void Win();
void Box(int bm);
int Lose();

int main(void)
{
	PlayerX = 1, PlayerY = 1;

	int i, j;

    

	//マップ生成
	for (i = 0; i < Y; i++)
	{
		for (j = 0; j < X; j++)
		{
			if (map[i][j] == 1)
			{
				printf("壁");
			}
			else if (i == PlayerY && j == PlayerX)
			{
				printf("Ｐ");
				
			}
			else if (i==Box_Y && j == Box_X)
			{
				printf("箱");
			}
			else if (i == Goal_Y && j == Goal_X)
			{
				printf("・");
			}
			else
			{
				printf("  ");

			}
		}
		printf("\n");
	}

	//テキストの表示
	printf("移動方向を入力(テンキー十字方向)\n");
	printf("左:4 右:6 上:8 下:2\n");

	

	while (1)
	{
		Move();
		
		
		for (i = 0; i < Y; i++)
		{
			for (j = 0; j < X; j++)
			{

				
				//入力後の表示
				if (map[i][j] == 1)
				{
					printf("壁");
				}
				//プレイヤーの現在地の表示
				else if (PlayerY == i && PlayerX == j )
				{
					printf("Ｐ");
				}
				//箱の位置
				else if (Box_Y == i && Box_X == j)
				{
					printf("箱");
				}
				//ゴールの位置
				else if (Goal_Y == i && Goal_X == j)
				{
					printf("・");
					map[Goal_Y][Goal_X] = 4;
				}
				else
				{
					printf("  ");
				}


			}
			printf("\n");



		}

		//ゲームのクリア条件のチェック
		if ( 4 == map[Box_Y][Box_X])
		{
			Win();
			break;
		}

		//ゲームのオーバ条件のチェック
		if (!Lose())
		{
			printf("ゲームオーバー\n");
			break;
		}
		//テキストの表示
		printf("移動方向を入力(テンキー十字方向)\n");
		printf("左:4 右:6 上:8 下:2\n");

	}

	return 0;
}

//プレイヤーの移動の関数
void Move()
{
	int key = 0;

	int Box_Move = 0;

	scanf_s("%d", &key);

	//左
	if (key == 4 && map[PlayerY][PlayerX - 1] == 0)
	{
        PlayerX--;
		if (map[PlayerY][PlayerX - 1] == 2)
		{
			printf("あ");
		}
	}
	//右
	else if (key == 6 && map[PlayerY][PlayerX + 1] == 0 )
	{
       PlayerX++;
	  
	   //右にプレイヤーがおり、右に入力された後、箱が進方向に壁がなかったら箱が進む
	 
	   Box_Move = 6;
	   Box(Box_Move);
	}
		

	//上
	else if (key == 8 && map[PlayerY - 1][PlayerX] == 0)
	{
      PlayerY--;

	  //上にプレイヤーがおり、上に入力された後、箱が進方向に壁がなかったら箱が進む
	  /*if (map[PlayerY - 1][PlayerX] == map[Box_Y][Box_X])
	  {
		  Box_Move = 8;
		  Box(Box_Move);
	  }*/
	}
		

	//下
	else if (key == 2 && map[PlayerY + 1][PlayerX] == 0)
	{
       PlayerY++;

	   //下にプレイヤーがおり、下に入力された後、箱が進方向に壁がなくなったら箱が進む
		   Box_Move = 2;
		   Box(Box_Move);
	   
	}
		

}

//箱移動の関数
void Box(int bm)
{
	switch (bm)
	{
	case 4:
		//左にプレイヤーがおり、左を入力された後、箱が進む方向に壁がなかったら箱が進む
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

//ゲームクリアの関数
void Win()
{
	printf("クリア\n");
}

//ゲームオーバーの関数
int Lose()
{
	//周りに0(進める）マスか確かめる
	if (map[PlayerY][PlayerX + 1] == 0 || map[PlayerY][PlayerX - 1] == 0 || map[PlayerY - 1][PlayerX] == 0 || map[PlayerY + 1][PlayerX] == 0)
	{
		return 1;
	}
	return 0;
}