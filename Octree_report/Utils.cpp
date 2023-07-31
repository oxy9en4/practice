#include "stdafx.h"
#include "Utils.h"



bool Box::operator ==(Box& p)
{
	if (fabs(v.x - p.v.x) < EPSILON
		&& fabs(v.y - p.v.y) < EPSILON
		&& fabs(v.z - p.v.z) < EPSILON
		&& fabs(s.width - p.s.width) < EPSILON
		&& fabs(s.height - p.s.height) < EPSILON
		&& fabs(s.depth - p.s.depth) < EPSILON)
	{
		return true;
	}
	return false;
}

bool Box::operator !=(Box& p) {
	return !(*this == p);
}

Box Box::operator +(Box& p) {
	float fMinX = min(v.x, p.v.x);
	float fMinY = min(v.y, p.v.y);
	float fMinZ = min(v.z, p.v.z);
	float fMaxX = max(v.x, p.v.x);
	float fMaxY = max(v.y, p.v.y);
	float fMaxZ = max(v.z, p.v.z);
	Vector3 pivot = { fMinX, fMinY, fMinZ };
	Box tmp(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
	return tmp;
}

Box Box::operator -(Box& p) {
	Box tmp;
	tmp.mBenable = false;

	if (ToBox(p)) {

		float fMinX = max(mMin.v.x, p.mMin.v.x);
		float fMinY = max(mMin.v.y, p.mMin.v.y);
		float fMinZ = max(mMin.v.z, p.mMin.v.z);

		float fMaxX = min(mMax.v.x, p.mMax.v.x);
		float fMaxY = min(mMax.v.y, p.mMax.v.y);
		float fMaxZ = min(mMax.v.z, p.mMax.v.z);

		Vector3 pivot(fMinX, fMinY, fMinZ);
		tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
		tmp.mBenable = true;
	}
	return tmp;
}
Box Box::operator -(Vector3& p) {
	return Box(v.x - p.v.x, v.y - p.v.y, v.z - p.s.z, s.width, s.height, s.depth);
}
Box Box::operator *(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x * f, v.y * f, v.z * f, s.width, s.height, s.depth);
}
Box Box::operator /(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x / f, v.y / f, v.z / f, s.width, s.height, s.depth);
}


void Box::Set(float w, float h, float d) {
	v.width = w;
	v.height = h;
	v.depth = d;
	mHalf = { w * 0.5f, h * 0.5f, d * 0.5f };
	mVector3[0] = { v.x, v.y, v.z };
	mVector3[1] = { v.x + w, v.y, v.z };
	mVector3[2] = { v.x + w, v.y + h, v.z };
	mVector3[3] = { v.x, v.y + h, v.z };

	mVector3[4] = { v.x, v.y, v.z + d };
	mVector3[5] = { v.x + w, v.y, v.z + d };
	mVector3[6] = { v.x + w, v.y + h, v.z + d };
	mVector3[7] = { v.x, v.y + h, v.z + d };

	mMin = mVector3[0];
	mMax = mVector3[6];
	mCenter = (mMin + mMax) * 0.5f;
}

void Box::Set(float x, float y, float z, float w, float h, float d) {
	v.x = x;
	v.y = y;
	v.z = z;

	Set(w, h, d);
}

void Box::Set(Vector3 p, float w, float h, float d) {
	v.x = p.v.x;
	v.y = p.v.y;
	v.z = p.v.z;
	Set(w, h, d);
}

bool Box::ToBox(Box& p) {
	Box sum = (*this) + p;

	if (sum.v.x - (s.width + p.s.width) < EPSILON
		&& sum.v.y - (s.height + p.s.height) < EPSILON
		&& sum.v.z - (s.depth + p.s.depth) < EPSILON)
	{
		return true;
	}
	return false;
}


static bool BoxToBox(Box& p, Box& t) {
	Box sum = p + t;

	if (sum.v.x - (p.s.width + t.s.width) > EPSILON) return false;
	if (sum.v.y - (p.s.height + t.s.height) > EPSILON) return false;
	if (sum.v.z - (p.s.depth + t.s.depth) > EPSILON) return false;
	return true;
}