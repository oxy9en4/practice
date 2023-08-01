#include "stdafx.h"
#include "Utils.h"



bool Box::operator ==(Box& p)
{
	if (fabs(v.x - p.v.x) < EPSILON
		&& fabs(v.y - p.v.y) < EPSILON
		&& fabs(v.z - p.v.z) < EPSILON
		&& fabs(mfWidth - p.mfWidth) < EPSILON
		&& fabs(mfHeight - p.mfHeight) < EPSILON
		&& fabs(mfDepth - p.mfDepth) < EPSILON)
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
	return Box(v.x - p.x, v.y - p.y, v.z - p.z, mfWidth, mfHeight, mfDepth);
}
Box Box::operator *(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x * f, v.y * f, v.z * f, mfWidth, mfHeight, mfDepth);
}
Box Box::operator /(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x / f, v.y / f, v.z / f, mfWidth, mfHeight, mfDepth);
}


void Box::Set(float w, float h, float d) {
	mfWidth = w;
	mfHeight = h;
	mfDepth = d;
	mHalf = { w * 0.5f, h * 0.5f, d * 0.5f };
	mPoint[0] = { v.x, v.y, v.z };
	mPoint[1] = { v.x + w, v.y, v.z };
	mPoint[2] = { v.x + w, v.y + h, v.z };
	mPoint[3] = { v.x, v.y + h, v.z };

	mPoint[4] = { v.x, v.y, v.z + d };
	mPoint[5] = { v.x + w, v.y, v.z + d };
	mPoint[6] = { v.x + w, v.y + h, v.z + d };
	mPoint[7] = { v.x, v.y + h, v.z + d };

	mMin = mPoint[0];
	mMax = mPoint[6];
	mCenter = (mMin + mMax) * 0.5f;
}

void Box::Set(float x, float y, float z, float w, float h, float d) {
	v.x = x;
	v.y = y;
	v.z = z;

	Set(w, h, d);
}

void Box::Set(Vector3 p, float w, float h, float d) {
	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	Set(w, h, d);
}


bool Box::ToBox(Box& p) {
	Box sum = (*this) + p;

	if (sum.v.x - (mfWidth + p.mfWidth) < EPSILON
		&& sum.v.y - (mfHeight + p.mfHeight) < EPSILON
		&& sum.v.z - (mfDepth + p.mfDepth) < EPSILON)
	{
		return true;
	}
	return false;
}


static bool BoxToBox(Box& p, Box& t) {
	Box sum = p + t;

	if (sum.v.x - (p.mfWidth + t.mfWidth) > EPSILON) return false;
	if (sum.v.y - (p.mfHeight + t.mfHeight) > EPSILON) return false;
	if (sum.v.z - (p.mfDepth + t.mfDepth) > EPSILON) return false;
	return true;
}