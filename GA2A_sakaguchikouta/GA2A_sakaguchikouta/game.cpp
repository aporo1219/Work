//�Q�[���V�[��
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include"circle.h"
#include"enemy.h"
#include"obstacles.h"
#include"dispenser.h"




//extern(�X�R�A�j�̏�����
int GSCORE{ 0 };
bool VANISH{ true };
int GLIFE{ 5 };


void GameOver();

//�R���X�g���N�^
CGame::CGame(CManager* p) :CScene(p) {
	base.emplace_back((unique_ptr<Base>)new CEnemy(400,200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_LEFT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_DOWN(400, 200));
	base.emplace_back((unique_ptr<Base>)new CDispenser(400, 200));
}

//�X�V����
int CGame::Update() {
	if (GLIFE <= 0)
	{
		GameOver();
		
		
	}
	
	//�N���b�N�����ꍇ
	{
		
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !mouse_left && VANISH == true && GLIFE > 0)
		{
			int x,y;
			GetMousePoint(&x, &y);
			base.emplace_back((unique_ptr<Base>)new CCircle(x, y));
			VANISH = false;
		}
		
	}
	//list�I�u�W�F�N�g�̍X�V����
	for (auto i = base.begin(); i != base.end(); i++)
		(*i)->Action(base);

	//���X�g�̃T�C�Y�ۑ�
	temp_list_Length = (int)base.size();

	//���X�g����̃I�u�W�F�N�g�폜����
	for (auto i = base.begin(); i != base.end();)
		(*i)->FLAG ? i++ : i = base.erase(i);

	//�}�E�X�̍��N���b�N��Ԃ�ۑ�
	mouse_left = (GetMouseInput() & MOUSE_INPUT_LEFT);
	return 0;
}

//�`�揈��
void CGame::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "List_Size = %d", base.size());
	DrawFormatString(400, 0, GetColor(255, 255, 0), "SCORE = %d", GSCORE);
	DrawFormatString(400, 16, GetColor(0, 255, 0), "���C�t = %d", GLIFE);
	DrawFormatString(400, 32, GetColor(255, 255, 255), "���F�͔����͂�����");
	DrawFormatString(400, 48, GetColor(255, 255, 255), "�Ԃ̓X�R�A�ƃ��C�t������");
	DrawFormatString(400, 64, GetColor(255, 255, 255), "�̓��C�t����");
	DrawFormatString(400, 80, GetColor(255, 255, 255), "�����Ă���~�̓X�R�A�A�b�v");
	DrawBox(400, 0, 650, 100, GetColor(0, 255, 255), false);
	
	//list�I�u�W�F�N�g�̕`��
	for (auto i = base.begin(); i != base.end(); i++)
		if ((*i)->FLAG) (*i)->Draw();

	//3D���̕`��
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 0, 100),
	//	0x0000ff
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(100, 0, 0),
	//	0xff0000
	//);
	//DrawLine3D(
	//	VGet(0, 0, 0),
	//	VGet(0, 100, 0),
	//	0x00ff00
	//);
}

CGame::~CGame()
{

}

void GameOver()
{	 
	DrawString(400, 160, "�����܂�" ,GetColor(255, 255, 255));
	DrawFormatString(400, 176, GetColor(255, 0, 0),"�X�R�A��%d�ł��B",GSCORE);
}
