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
	float mfWidth = 0.0f;
	float mfHeight = 0.0f;
	float mfDepth = 0.0f;

	bool operator ==(Box& p);

	bool operator !=(Box& p);

	Box operator +(Box& p);

	Box operator -(Box& p);
	Box operator -(Vector3& p);
	Box operator *(float f);
	Box operator /(float f);


	void Set(float w, float h, float d);

	void Set(float x, float y, float z, float w, float h, float d);

	void Set(Vector3 p, float w, float h, float d);

	void Set(Vector3 p, Vector3 o);

	bool ToBox(Box& p);

	static bool BoxToBox(Box& p);


	Box(Vector3 p, float w, float h, float d)
	{
		Set(p.x, p.y, p.z, w, h, d);
	}

	Box(float x, float y, float z, float w, float h, float d)
	{
		Set(x, y, z, w, h, d);
	}

	Box() = default;
};
