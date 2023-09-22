#pragma once
#include "aMath.h"
#include "TMath.h"

struct UVRect
{
	Vector2 m_Min;
	Vector2 m_Max;
};

struct TRect
{
	bool mbEnable = true;
	float m_fWidth = 0.0f;
	float m_fHeight = 0.0f;
	Vector2 m_Point[4];
	Vector2 m_Center;
	Vector2 m_Half;
	Vector2 m_Min;
	Vector2 m_Max;
	Vector2 v;
	Vector2 s;

	bool operator == (TRect& p);
	bool operator != (TRect& p);
	TRect operator + (TRect& p);
	TRect operator - (TRect& p);
	TRect operator - (Vector2& p);
	TRect operator * (float fValue);
	TRect operator / (float fValue);
	void Set(Vector2 p);
	void Set(float fw, float fh);
	void Set(Vector2 p, float fw, float fh);
	void Set(float fx, float fy, float fw, float fh);

	bool ToRect(TRect& rt);
	bool ToPoint(Vector2& p);
	TRect();
	TRect(float fx, float fy, float fw, float fh);
};

struct T_AABB
{
	// AABB
	TVector3   vMax;
	TVector3   vMin;
};
struct T_OBB
{
	// AABB
	TVector3   vCenter;
	TVector3   vAxis[3];
	float      fExtent[3];
};
struct T_BOX
{
	TVector3   vPos[8];
	TVector3   vMax;
	TVector3   vMin;
	TVector3   vCenter;
	TVector3   vAxis[3];
	float      fExtent[3];
};
// make classes for  octree

struct Box {
	bool mbEnable = true;							// Box�� �̿밡���Ѱ�?

	Vector3 mPoint[8];								// Box�� �ܰ� ����(vertex)���� �����ϴ� ����
	Vector3 mCenter;								// Box�� ����
	Vector3 mHalf;									// Box�� ���� ���� ������ ����. �̰��� ����س��� ������ Tree���� �ڽĳ�带 ������ �� �ʿ�
	Vector3 mMin;									// Box���� ���� ���� x y z�� ����. �ڽĳ�� ������ �浹 �˻翡 �ʿ�
	Vector3 mMax;									// Box���� ���� ū x y z�� ����
	Vector3 v;										// Box�� ��ġ����. position(pivot)
	Vector3 size;									// Box�� ��������. size.x = width, size.y = height, size.z = depth

	bool operator ==(Box& p);						// ���� Box���� �˻�

	bool operator !=(Box& p);						// �ٸ� Box���� ��ȯ

	Box operator +(Box& p);							// Box�� ����. �� Box�� ��� �����ϴ� ū Box�� ������. �浹 �˻� �� �ʿ�
									// �ʿ��ϴٸ� operator +(Vector3& p)�� ����� Box�� ��ġ�� Vector��ŭ �̵���Ű�� �Լ��� �����ε��� ���� ����
	Box operator -(Box& p);							// Box���� ��. ���������� �浹 �˻� �� Ȱ�� ����
	Box operator -(Vector3& p);						// Box ��ġ�� Vector��ŭ �̵���Ű�� �Լ�(- negativ)�ϰ�
	Box operator *(float f);						// Box�� ��ġ�� f��ŭ ���� ��. ��� ũ�⸦ ���ϴ� �ǹ̰� ��ġ�� ������ ��뿡 ����
	Box operator /(float f);


	void Set(float fw, float fh, float fd);
	void Set(float fx, float fy, float fz, float fw, float fh, float fd);
	void Set(Vector3 p, float fw, float fh, float fd);
	void Set(Vector3 p, Vector3 o);

	bool ToBox(Box& p);

	static bool BoxToBox(Box& p, Box& t);


	Box(Vector3 p, float fw, float fh, float fd)
	{
		Set(p.x, p.y, p.z, fw, fh, fd);
	}

	Box(float fx, float fy, float fz, float fw, float fh, float fd)
	{
		Set(fx, fy, fz, fw, fh, fd);
	}

	Box() {};
};

struct Sphere
{
	Vector3 vCenter;
	float fRadius;
};

struct Circle
{
	Vector2 vCenter;
	float fRadius;
};
