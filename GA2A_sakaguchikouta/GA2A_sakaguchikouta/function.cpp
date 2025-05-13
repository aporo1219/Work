#pragma once
#include "function.h"
#include <random>

//���W + �x�N�g��
Point Add_Point_Vector(Point p0, Vector v0) {Point r;	r.x = p0.x + v0.x;	r.y = p0.y + v0.y;	return r; }
//���W - ���W
Vector Sub_Point_Point(Point p0, Point p1) { Vector r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	return r; }
//�x�N�g�� - �x�N�g��
Vector Sub_Vector_Vector(Vector p0, Vector p1) { Vector r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	return r; }
//�x�N�g�� + �x�N�g��
Vector Add_Vector_Vector(Vector v0, Vector v1) { Vector r;	r.x = v0.x + v1.x;	r.y = v0.y + v1.y;	return r; }
//�x�N�g�� �~ �X�J���[
Vector Mul_Vector_Scaler(Vector v, float s) { Vector r;	r.x = v.x * s;	r.y = v.y * s;	return r; }
//�x�N�g���̒���
float Vector_Length(Vector v) { float l = sqrtf((v.x * v.x + v.y * v.y));	return l; }
//�x�N�g���̐��K��
Vector Vector_Normalize(Vector v) { float l = Vector_Length(v);	Vector n;	n.x = v.x / l;	n.y = v.y / l;	return n; }
//�x�N�g���̒�����ݒ�
Vector Vector_SetLength(Vector v, float length) { v = Vector_Normalize(v);	v = Mul_Vector_Scaler(v, length);	return v; }
//���W + �x�N�g��
Point3 Add_Point_Vector(Point3 p0, Vector3 v0){	Point3 r;	r.x = p0.x + v0.x;	r.y = p0.y + v0.y;	r.z = p0.z + v0.z;	return r;}
//���W - ���W
Vector3 Sub_Point_Point(Point3 p0, Point3 p1){	Vector3 r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	r.z = p0.z - p1.z;	return r;}
//�x�N�g�� - �x�N�g��
Vector3 Sub_Vector_Vector(Vector3 p0, Vector3 p1){	Vector3 r;	r.x = p0.x - p1.x;	r.y = p0.y - p1.y;	r.z = p0.z - p1.z;	return r;}
//�x�N�g�� + �x�N�g��
Vector3 Add_Vector_Vector(Vector3 v0, Vector3 v1){	Vector3 r;	r.x = v0.x + v1.x;	r.y = v0.y + v1.y;	r.z = v0.z + v1.z;	return r;}
//�x�N�g�� �~ �X�J���[
Vector3 Mul_Vector_Scaler(Vector3 v, float s){	Vector3 r;	r.x = v.x * s;	r.y = v.y * s;	r.z = v.z * s;	return r;}
//�x�N�g���̒���
float Vector_Length(Vector3 v){	float l = sqrtf((v.x * v.x + v.y * v.y + v.z * v.z));	return l;}
//�x�N�g���̐��K��
Vector3 Vector_Normalize(Vector3 v){	float l = Vector_Length(v);	Vector3 n;	n.x = v.x / l;	n.y = v.y / l;	n.z = v.z / l;	return n;}
//�x�N�g���̒�����ݒ�
Vector3 Vector_SetLength(Vector3 v, float length) {	v = Vector_Normalize(v);	v = Mul_Vector_Scaler(v, length);	return v;}
//�O��(3D)
Vector3 Vector3_Cross(Vector3 v1, Vector3 v2) {	Vector3 v;	v.x = v1.y * v2.z - v1.z * v2.y;	v.y = v1.z * v2.x - v1.x * v2.z;	v.z = v1.x * v2.y - v1.y * v2.x;	return v;}
//����(3D)
float Vector3_Dot(Vector3 v1, Vector3 v2) {	float r;	r = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);	return r;}

//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(Vector3 vec, float angle) {	Vector3 v;	vec = Vector_Normalize(vec);	v.x = 0.0f;	v.y = cos(RADIAN(angle)) * vec.y + sin(RADIAN(angle)) * vec.z;	v.z = -sin(RADIAN(angle)) * vec.y + cos(RADIAN(angle)) * vec.z;	return v;}
//�w�肵���p�x�ɉ�](x����])
Vector3 Vector_Rotation_X(float angle) {	Vector3 v;	v.x = 0.0f;	v.y = cos(RADIAN(angle)) + sin(RADIAN(angle));	v.z = -sin(RADIAN(angle)) + cos(RADIAN(angle));	return v;}

//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(Vector3 vec, float angle) {	Vector3 v;		vec = Vector_Normalize(vec);v.x = cos(RADIAN(angle)) * vec.x - sin(RADIAN(angle)) * vec.z;	v.y = 0.0f;	v.z = sin(RADIAN(angle)) * vec.x + cos(RADIAN(angle)) * vec.z;	return v;}
//�w�肵���p�x�ɉ�](y����])
Vector3 Vector_Rotation_Y(float angle) {	Vector3 v;	v.x = cos(RADIAN(angle)) - sin(RADIAN(angle));	v.y = 0.0f;	v.z = sin(RADIAN(angle)) + cos(RADIAN(angle));	return v;}

//�x�N�g���ɑ΂��Ďw�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(Vector3 vec, float angle) {	Vector3 v;	vec = Vector_Normalize(vec);	v.x = cos(RADIAN(angle)) * vec.x + sin(RADIAN(angle)) * vec.y;	v.y = -sin(RADIAN(angle)) * vec.x + cos(RADIAN(angle)) * vec.y;	v.z = 0.0f;	return v;}
//�w�肵���p�x�ɉ�](z����])
Vector3 Vector_Rotation_Z(float angle) {	Vector3 v;	v.x = cos(RADIAN(angle)) + sin(RADIAN(angle));	v.y = -sin(RADIAN(angle)) + cos(RADIAN(angle));	v.z = 0.0f;	return v;}

//��`����(x1,y1,x2,y2,w,h)
int HitCheck_box(float x1, float y1, float x2, float y2, int w, int h) {
	if (x1 < x2 + w && x2 < x1 + w && y1 < y2 + h && y2 < y1 + h)
		return 1;
	return 0;
}

//��`����Q(x1,y1,x2,y2,w1,h1,w2,h2)
int HitCheck_box(float x1, float y1, float x2, float y2, int w1, int h1, int w2, int h2) {
	if (x1 < x2 + w2 && x2 < x1 + w1 &&	y1 < y2 + h2 && y2 < y1 + h1)
		return 1;
	return 0;
}

//��`����3(�I�u�W�F�N�g,�I�u�W�F�N�g)
//�摜�T�C�Y(ImgWidth,ImgHeight)�Ŕ���
int HitCheck_box(Base* a, Base* b){
	if (a->pos.x < b->pos.x + b->ImgWidth &&
		b->pos.x < a->pos.x + a->ImgWidth &&
		a->pos.y < b->pos.y + b->ImgHeight &&
		b->pos.y < a->pos.y + a->ImgHeight)
		return 1;
	return 0;
}

//AABB����
bool HitCheck_AABB(Base3D* a, Base3D* b) {
	MINMAX A(a->pos, a->b_box);
	MINMAX B(b->pos, b->b_box);

	if (
		A.min.x <= B.max.x &&
		A.max.x >= B.min.x &&
		A.min.y <= B.max.y &&
		A.max.y >= B.min.y &&
		A.min.z <= B.max.z &&
		A.max.z >= B.min.z
		)
		return true;
	return false;
}
bool HitCheck_AABB(MINMAX a, MINMAX b) {
	if (
		a.min.x < b.max.x &&
		a.max.x > b.min.x &&
		a.min.y < b.max.y &&
		a.max.y > b.min.y &&
		a.min.z < b.max.z &&
		a.max.z > b.min.z
		)
		return true;
	return false;
}
//������(�ʒuA,���aA,�ʒuB,���aB)
bool HitCheck_Sphere(Point3 A, float RA, Point3 B, float RB) {
	if (DistanceF(A, B) < RA + RB)
		return true;
	return false;
}

//�~�Ƌ�`����p�֐��i��`�̈�ԋ߂��ʒu���v�Z�j
float Circle_Center_With_Closest_Point(float a, float b, float c)
{
	if (a < b) {
		return b;
	}
	else if (a > c) {
		return c;
	}
	else {
		return a;
	}
}
//�~�Ƌ�`���菈��(�~�I�u�W�F�N�g,��`�I�u�W�F�N�g,�~�̔��a)
void HitCheck_Box_Circle(Base* a, Base* b, float radius) {
	Point pc{ a->pos.x + a->vec.x + a->ImgWidth / 2,a->pos.y + a->vec.y + a->ImgHeight / 2 };//���S���W�v�Z
	Point n{ -1,-1 };//��`�̈�ԋ߂����W
	n.x = Circle_Center_With_Closest_Point(pc.x, b->pos.x, b->pos.x + b->ImgWidth);
	n.y = Circle_Center_With_Closest_Point(pc.y, b->pos.y, b->pos.y + b->ImgHeight);

	float l = DistanceF(pc.x, pc.y, n.x, n.y);//��ԋ߂����W���璆�S�܂ł̋���
	if (l < radius)//���aradius�Ŕ���
	{
		Vector v{ n.x - pc.x, n.y - pc.y };//�����x�N�g��
		v = Vector_Normalize(v);//�����x�N�g�����K��
		v = Vector_SetLength(v, radius - l);
		a->vec.x -= (int)v.x;
		a->vec.y -= (int)v.y;
	}
}
//�w��͈̗͂������擾(min,max)
int Range_Random_Number(int min, int max)
{
	random_device rd;
	default_random_engine engine(rd());
	uniform_int_distribution<int> dis(min, max);

	return dis(engine);
}
//�w��͈̗͂������擾(min,max)(32bit��)
float Range_Random_NumberF(float min, float max)
{
	random_device rd;
	mt19937 engine(rd());
	uniform_real_distribution<float> dis(min, max);

	return dis(engine);
}

/*
* �����������֐�
//int Range_Random_Number(int min, int max)
//{
//	return (rand() % (max - min + 1)) + min;
//}
*/

//��_�ԋ���
float DistanceF(float a, float b, float c, float d)
{
	return sqrtf((a - c) * (a - c) + (b - d) * (b - d));
}
float DistanceF(Point3 A, Point3 B) {
	float r;
	r = sqrtf((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
	return r;
}

//�S�ẴL�[���A�������܂őҋ@
void WAIT_RELEASE_ALL_KEY()
{
	while (true)
	{
		if (CheckHitKeyAll() == 0) break;
	}
}
//�S�ẴL�[���A�������܂őҋ@�i�^�C�v�w��j
//DX_CHECKINPUT_KEY : DX_CHECKINPUT_PAD : DX_CHECKINPUT_MOUSE
void WAIT_RELEASE_ALL_KEY(int type)
{
	while (true)
	{
		if (CheckHitKeyAll(type) == 0) break;
	}
}

//���l�̕`��i�摜�n���h��, �ꌅ�ڂ̈ʒux, �ꌅ�ڂ̈ʒuy, �l, �����T�C�Yw, �����T�C�Yh)
void DrawNum(int img, int x, int y, int num, int w, int h)
{
	//���v�Z�i�\���ʒu�Ɏg�p�j
	int digits{ 0 };
	int tmp_num = num;

	while (true)
	{
		DrawRectGraph(
			x - w / 2 - digits * w, y,
			(int)tmp_num % 10 * w, 0,
			w, h,
			img,
			true
		);
		tmp_num = tmp_num / 10;
		digits++;
		if (tmp_num == 0) break;
	}
}

//���X�g����w��I�u�W�F�N�g�̎擾
Base* Get_obj(list<unique_ptr<Base>>& base, int ID)
{
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == ID)
		{
			return (*i).get();
		}
	}
	return nullptr;
}

//���X�g����w��I�u�W�F�N�g�̎擾
Base3D* Get_obj(list<unique_ptr<Base3D>>& base, int ID)
{
	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == ID)
		{
			return (*i).get();
		}
	}
	return nullptr;
}

//�w�肵���I�u�W�F�N�g�̍��W�擾
Point Get_Point(list<unique_ptr<Base>>& base, int ID)
{
	Point p{ 0,0 };

	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID == ID) return (*i)->pos;
	}
	return p;
}

//�w�肵���I�u�W�F�N�g�ȊO�����X�g����폜
void Del_SpecifiedObj(list<unique_ptr<Base>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID != ID) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}

//�w��I�u�W�F�N�g�����X�g����폜(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>& base, int ID) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID == ID) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}

//�w��I�u�W�F�N�g�����X�g����폜�͈�(FLAG��false�ɂ���)
void Del_ListObj(list<unique_ptr<Base>>& base, int ID, int ID2) {
	for (auto i = base.begin(); i != base.end(); i++) {
		if ((*i)->ID >= ID && (*i)->ID <= ID2) {
			(*i)->FLAG = false;
			(*i)->ID = -1;
		}
	}
}