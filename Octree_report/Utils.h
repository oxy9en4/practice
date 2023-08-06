#pragma once
#include "Math.h"



// make classes for  octree

struct Box {
	bool mbEnable = true;

	Vector3 mPoint[8];
	Vector3 mCenter;
	Vector3 mHalf;
	Vector3 mMin;
	Vector3 mMax;
	Vector3 v;
	Vector3 size;

	bool operator ==(Box& p);

	bool operator !=(Box& p);

	Box operator +(Box& p);

	Box operator -(Box& p);
	Box operator -(Vector3& p);
	Box operator *(float f);
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
