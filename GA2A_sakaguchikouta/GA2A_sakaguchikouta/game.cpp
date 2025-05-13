//�Q�[���V�[��
#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"

#include"circle.h"
#include"enemy.h"
#include"obstacles.h"


//extern(�X�R�A�j�̏�����
int GSCORE{ 0 };

//�R���X�g���N�^
CGame::CGame(CManager* p) :CScene(p) {
	base.emplace_back((unique_ptr<Base>)new CEnemy(400,200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_LEFT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_UP(400, 200));
	base.emplace_back((unique_ptr<Base>)new CObstacles_RIGHT_DOWN(400, 200));
}

//�X�V����
int CGame::Update() {
        
	//�N���b�N�����ꍇ
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !mouse_left)
		{
			int x,y;
			GetMousePoint(&x, &y);
			base.emplace_back((unique_ptr<Base>)new CCircle(x, y));
			
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
	DrawFormatString(0, 16, GetColor(255, 255, 255), "SCORE = %d", GSCORE);
	
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
