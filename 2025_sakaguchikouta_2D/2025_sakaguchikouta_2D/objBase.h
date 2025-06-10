#pragma once
#include "main.h"
#include "objChar.h"

using namespace std;

//�I�u�W�F�N�g�x�[�X�N���X
class Base : public Character{
public:
	int pri{ 0 };//�`��̏���
	int ID{ -1 };//�I�u�W�F�N�gID
	bool FLAG{ true };//�I�u�W�F�N�g���݃t���O
	bool draw_flag{ true };//�I�u�W�F�N�g�̕`��t���O

	virtual int Action(list<unique_ptr<Base>>&) = 0;
	virtual void Draw() = 0;
};

//�I�u�W�F�N�g�̃\�[�g�N���X
class sort
{
public:
	bool operator()(const unique_ptr<Base>& x, const unique_ptr<Base>& y) const
	{
		return x.get()->pri < y.get()->pri;
	}
};

//3D�p
class Base3D : public Character3D {
public:
	int ID{ -1 };//�I�u�W�F�N�gID
	bool FLAG{ true };//�I�u�W�F�N�g���݃t���O
	bool draw_flag{ true };//�I�u�W�F�N�g�̕`��t���O

	virtual int Action(list<unique_ptr<Base3D>>&) = 0;
	virtual void Draw() = 0;
};
