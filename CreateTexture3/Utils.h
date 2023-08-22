#pragma once
#include "stdafx.h"
#include "Math.h"

struct Rect
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

	bool operator == (Rect& p);
	bool operator != (Rect& p);
	Rect operator + (Rect& p);
	Rect operator - (Rect& p);
	Rect operator - (Vector2& p);
	Rect operator * (float fValue);
	Rect operator / (float fValue);
	void Set(Vector2 p);
	void Set(float fw, float fh);
	void Set(Vector2 p, float fw, float fh);
	void Set(float fx, float fy, float fw, float fh);

	bool ToRect(Rect& rt);
	bool ToPoint(Vector2& p);
	Rect();
	Rect(float fx, float fy, float fw, float fh);
};


// make classes for  octree

struct Box {
	bool mbEnable = true;							// Box가 이용가능한가?

	Vector3 mPoint[8];								// Box의 외곽 정점(vertex)들을 보관하는 벡터
	Vector3 mCenter;								// Box의 중점
	Vector3 mHalf;									// Box의 가로 세로 높이의 절반. 이것을 계산해놓는 이유는 Tree에서 자식노드를 생성할 때 필요
	Vector3 mMin;									// Box에서 가장 작은 x y z를 보관. 자식노드 생성과 충돌 검사에 필요
	Vector3 mMax;									// Box에서 가장 큰 x y z를 보관
	Vector3 v;										// Box의 위치정보. position(pivot)
	Vector3 size;									// Box의 부피정보. size.x = width, size.y = height, size.z = depth

	bool operator ==(Box& p);						// 같은 Box인지 검사

	bool operator !=(Box& p);						// 다른 Box인지 반환

	Box operator +(Box& p);							// Box를 더함. 두 Box를 모두 포함하는 큰 Box를 생성함. 충돌 검사 시 필요
									// 필요하다면 operator +(Vector3& p)를 만들어 Box의 위치만 Vector만큼 이동시키는 함수를 오버로딩할 수도 있음
	Box operator -(Box& p);							// Box끼리 뺌. 마찬가지로 충돌 검사 시 활용 가능
	Box operator -(Vector3& p);						// Box 위치를 Vector만큼 이동시키는 함수(- negativ)하게
	Box operator *(float f);						// Box의 위치를 f만큼 곱해 줌. 사실 크기를 곱하는 의미가 겹치기 때문에 사용에 주의
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
