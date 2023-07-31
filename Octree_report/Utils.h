#pragma once
#include <math.h>
#include <Math.h>

// make classes for  octree

struct Point {
	float mFx = 0.0f;
	float mFy = 0.0f;
	float mFz = 0.0f;


	bool operator ==(Point& p);

	bool operator !=(Point& p);

	Point operator +(Point& p);

	Point operator -(Point& p);

	Point operator*(float f);

	Point operator/(float f);

	Point& operator +=(Point& p);
	Point& operator /=(float f);

	float GetDistance();

	Point() = default;
	Point(float x, float y, float z) : mFx(x), mFy(y), mFz(z) {

	}
};

struct Box {
	bool mBenable = true;

	Vector3 mVector3[8];
	Vector3 mCenter;
	Vector3 mHalf;
	Vector3 mMin;
	Vector3 mMax;
	Vector3 v;
	Vector3 s;

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
