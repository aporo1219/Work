#pragma once
#include "objBase.h"

//�ő�ŏ�
//(Point3 A, Point3 B) A �� B �Ԃ̍ő�ŏ�
//�ő�l�ŏ��l
struct MINMAX {
	Vector3 min{ 0,0,0 };
	Vector3 max{ 0,0,0 };

	//Point3 to Point3
	MINMAX(Point3 a, Point3 b) {
		min.x = a.x;
		min.y = a.y;
		min.z = a.z;

		max.x = a.x + b.x;
		max.y = a.y + b.y;
		max.z = a.z + b.z;
	}
	//Vector3 to Vector3
	MINMAX(Vector3 a, Vector3 b) {
		min.x = a.x;
		min.y = a.y;
		min.z = a.z;

		max.x = a.x + b.x;
		max.y = a.y + b.y;
		max.z = a.z + b.z;
	}
	//Point3 to Vector3
	MINMAX(Point3 a, Vector3 b) {
		min.x = a.x;
		min.y = a.y;
		min.z = a.z;

		max.x = a.x + b.x;
		max.y = a.y + b.y;
		max.z = a.z + b.z;
	}
};
//���W + �x�N�g��
Point Add_Point_Vector(Point, Vector);
//���W - ���W
Vector Sub_Point_Point(Point, Point);
//�x�N�g�� - �x�N�g��
Vector Sub_Vector_Vector(Vector, Vector);
//�x�N�g�� + �x�N�g��
Vector Add_Vector_Vector(Vector, Vector);
//�x�N�g�� �~ �X�J���[
Vector Mul_Vector_Scaler(Vector, float);
//�x�N�g���̒���
float Vector_Length(Vector);
//�x�N�g���̐��K��
Vector Vector_Normalize(Vector);
//�x�N�g���̒�����ݒ�
Vector Vector_SetLength(Vector, float);

//���W + �x�N�g��
Point3 Add_Point_Vector(Point3, Vector3);
//���W - ���W
Vector3 Sub_Point_Point(Point3, Point3);
//�x�N�g�� - �x�N�g��
Vector3 Sub_Vector_Vector(Vector3, Vector3);
//�x�N�g�� + �x�N�g��
Vector3 Add_Vector_Vector(Vector3, Vector3);
//�x�N�g�� �~ �X�J���[
Vector3 Mul_Vector_Scaler(Vector3, float);
//�x�N�g���̒���
float Vector_Length(Vector3);
//�x�N�g���̐��K��
Vector3 Vector_Normalize(Vector3);
//�x�N�g���̒�����ݒ�
Vector3 Vector_SetLength(Vector3, float);
//����(3D)
float Vector3_Dot(Vector3, Vector3);
//�O��(3D)
Vector3 Vector3_Cross(Vector3, Vector3);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(Vector3, float);
//�w�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(float);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(Vector3, float);
//�w�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(float);
//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(Vector3, float);
//�w�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(float);

//��`����(x1,y1,x2,y2,w,h)
int HitCheck_box(float, float, float, float, int, int);
//��`����Q(x1,y1,x2,y2,w1,h1,w2,h2)
int HitCheck_box(float, float, float, float, int, int, int, int);
//��`����3(�I�u�W�F�N�g,�I�u�W�F�N�g)
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
int HitCheck_box(Base*, Base*);

//AABB����(�I�u�W�F�N�g,�I�u�W�F�N�g)
bool HitCheck_AABB(Base3D*, Base3D*);
//AABB����
bool HitCheck_AABB(MINMAX, MINMAX);
//������(�ʒuA,���aA,�ʒuB,���aB)
bool HitCheck_Sphere(Point3, float, Point3, float);

//�~�Ƌ�`���菈��(�~�I�u�W�F�N�g,��`�I�u�W�F�N�g,�~�̔��a)
void HitCheck_Box_Circle(Base*, Base*, float);

//�w��͈̗͂������擾(min,max)
int Range_Random_Number(int, int);
float Range_Random_NumberF(float, float);

//��_�ԋ���
float DistanceF(float, float, float, float);
float DistanceF(Point3, Point3);

//�S�ẴL�[���A�������܂őҋ@
void WAIT_RELEASE_ALL_KEY();

//�S�ẴL�[���A�������܂őҋ@�i�^�C�v�w�� DX_CHECKINPUT_KEY : DX_CHECKINPUT_PAD : DX_CHECKINPUT_MOUS)
void WAIT_RELEASE_ALL_KEY(int);

//���l�̕`��i�摜�n���h��, �ꌅ�ڂ̈ʒux, �ꌅ�ڂ̈ʒuy, �l, �����T�C�Yw, �����T�C�Yh)
void DrawNum(int, int, int, int, int, int);

//���X�g����w��I�u�W�F�N�g�̎擾
Base* Get_obj(list<unique_ptr<Base>>&, int);
Base3D* Get_obj(list<unique_ptr<Base3D>>&, int);

//�w�肵���I�u�W�F�N�g�̍��W�擾
Point Get_Point(list<unique_ptr<Base>>&, int);

//�w�肵���I�u�W�F�N�g�ȊO�����X�g����폜
void Del_SpecifiedObj(list<unique_ptr<Base>>&, int);

//�w��I�u�W�F�N�g�����X�g����폜(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>&, int);

//�w��I�u�W�F�N�g�����X�g����폜�͈�(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>&, int, int);