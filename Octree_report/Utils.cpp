#include "stdafx.h"
#include "Utils.h"



bool Box::operator ==(Box& p)
{
	if (fabs(v.x - p.v.x) < EPSILON
		&& fabs(v.y - p.v.y) < EPSILON
		&& fabs(v.z - p.v.z) < EPSILON
		&& fabs(size.x - p.size.x) < EPSILON
		&& fabs(size.y - p.size.y) < EPSILON
		&& fabs(size.z - p.size.z) < EPSILON)
	{
		return true;
	}
	return false;
}

bool Box::operator !=(Box& p) {
	return !(*this == p);
}

Box Box::operator +(Box& p) {
	Box tmp;
	float fMinX = min(mMin.x, p.mMin.x);
	float fMinY = min(mMin.y, p.mMin.y);
	float fMinZ = min(mMin.z, p.mMin.z);
	float fMaxX = max(mMax.x, p.mMax.x);
	float fMaxY = max(mMax.y, p.mMax.y);
	float fMaxZ = max(mMax.z, p.mMax.z);
	Vector3 pivot = { fMinX, fMinY, fMinZ };
	tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
	return tmp;
}

Box Box::operator -(Box& p) {
	Box tmp;
	tmp.mbEnable = false;

	if (ToBox(p)) {

		float fMinX = max(mMin.x, p.mMin.x);
		float fMinY = max(mMin.y, p.mMin.y);
		float fMinZ = max(mMin.z, p.mMin.z);

		float fMaxX = min(mMax.x, p.mMax.x);
		float fMaxY = min(mMax.y, p.mMax.y);
		float fMaxZ = min(mMax.z, p.mMax.z);

		Vector3 pivot(fMinX, fMinY, fMinZ);
		tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
		tmp.mbEnable = true;
	}
	return tmp;
}
Box Box::operator -(Vector3& p) {
	return Box(v.x - p.x, v.y - p.y, v.z - p.z, size.x, size.y, size.z);
}
Box Box::operator *(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x * f, v.y * f, v.z * f, size.x, size.y, size.z);
}
Box Box::operator /(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x / f, v.y / f, v.z / f, size.x, size.y, size.z);
}


void Box::Set(float fw, float fh, float fd) {
	size.x = fw;
	size.y = fh;
	size.z = fd;
	mHalf = { fw * 0.5f, fh * 0.5f, fd * 0.5f };
	mPoint[0] = { v.x, v.y, v.z };
	mPoint[1] = { v.x + fw, v.y, v.z };
	mPoint[2] = { v.x + fw, v.y + fh, v.z };
	mPoint[3] = { v.x, v.y + fh, v.z };

	mPoint[4] = { v.x, v.y, v.z + fd };
	mPoint[5] = { v.x + fw, v.y, v.z + fd };
	mPoint[6] = { v.x + fw, v.y + fh, v.z + fd };
	mPoint[7] = { v.x, v.y + fh, v.z + fd };

	mMin = mPoint[0];
	mMax = mPoint[6];
	mCenter = (mMin + mMax) * 0.5f;
}

void Box::Set(float fx, float fy, float fz, float fw, float fh, float fd) {
	v = { fx, fy, fz };

	Set(fw, fh, fd);
}

void Box::Set(Vector3 p, float fw, float fh, float fd) {
	v = { p.x, p.y, p.z };
	Set(fw, fh, fd);
}

void Box::Set(Vector3 p, Vector3 o)
{
	v = { p.x, p.y, p.z };
	Set(o.x, o.y, o.z);
}


bool Box::ToBox(Box& p) {
	Box sum = (*this) + p; // 제대로 더해지는지 확인
	float fX = size.x + p.size.x;
	float fY = size.y + p.size.y;
	float fZ = size.z + p.size.z;
	if (sum.size.x - fX <= EPSILON
		&& sum.size.y - fY <= EPSILON
		&& sum.size.z - fZ <= EPSILON)
	{
		return true;
	}
	return false;
}


bool Box::BoxToBox(Box& p, Box& t) {
	Box sum = p + t;

	if (sum.v.x - (p.size.x + t.size.x) > EPSILON) return false;
	if (sum.v.y - (p.size.y + t.size.y) > EPSILON) return false;
	if (sum.v.z - (p.size.z + t.size.z) > EPSILON) return false;
	return true;
}