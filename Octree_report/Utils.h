#pragma once
#include <math.h>

// make classes for  octree

struct Point {
	float mFx = 0.0f;
	float mFy = 0.0f;
	float mFz = 0.0f;


	bool operator ==(Point& p) {
		if (fabs(mFx - p.mFx) > 0.0001f &&
			fabs(mFy - p.mFy) > 0.0001f &&
			fabs(mFz - p.mFz) > 0.0001f)
		{
			return true;
		}
		return false;
	}

	bool operator !=(Point& p) {
		return !((*this).operator==(p));
	}

	Point operator +(Point& p) {
		return Point(mFx + p.mFx, mFy + p.mFy, mFz - p.mFz);
	}

	Point operator -(Point& p) {
		return Point(mFx - p.mFx, mFy - p.mFy, mFz - p.mFz);
	}

	Point operator*(float f) {
		return Point(mFx * f, mFy * f, mFz * f);
	}

	Point operator/(float f) {
		return Point(mFx / f, mFy / f, mFz / f);
	}

	Point& operator +=(Point& p) {
		mFx += p.mFx;
		mFy += p.mFy;
		return *this;
	}
	Point& operator /=(float f) {
		mFx /= f;
		mFy /= f;
		return *this;
	}

	float GetDistance() {
		float fDist = sqrt(mFx * mFx + mFy * mFy + mFz * mFz);
		return fDist;
	}

	Point() = default;
	Point(float x, float y, float z) : mFx(x), mFy(y), mFz(z) {

	}
};

struct Box {
	bool mBenable = true;
	float mFx = 0.0f;
	float mFy = 0.0f;
	float mFz = 0.0f;

	float mFwidth = 0.0f;
	float mFheight = 0.0f;
	float mFdepth = 0.0f;

	Point mPoint[8];
	Point mCenter;
	Point mHalf;
	Point mMin;
	Point mMax;
	Point v;
	Point s;

	bool operator ==(Box& p)
	{
		if (fabs(mFx - p.mFx) < 0.0001f
			&& fabs(mFy - p.mFy) < 0.0001f
			&& fabs(mFz - p.mFz) < 0.0001f
			&& fabs(mFwidth - p.mFwidth) < 0.0001f
			&& fabs(mFheight - p.mFheight) < 0.0001f
			&& fabs(mFdepth - p.mFdepth) < 0.0001f)
		{
			return true;
		}
		return false;
	}

	bool operator !=(Box& p) {
		return !(*this == p);
	}

	Box operator +(Box& p) {
		float fMinX = min(mFx, p.mFx);
		float fMinY = min(mFy, p.mFy);
		float fMinZ = min(mFz, p.mFz);
		float fMaxX = max(mFx, p.mFx);
		float fMaxY = max(mFy, p.mFy);
		float fMaxZ = max(mFz, p.mFz);
		Point pivot = { fMinX, fMinY, fMinZ };
		Box tmp(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
		return tmp;
	}

	Box operator -(Box& p) {
		Box tmp;
		tmp.mBenable = false;

		if (ToBox(p)) {

			float fMinX = max(mMin.mFx, p.mMin.mFx);
			float fMinY = max(mMin.mFy, p.mMin.mFy);
			float fMinZ = max(mMin.mFz, p.mMin.mFz);

			float fMaxX = min(mMax.mFx, p.mMax.mFx);
			float fMaxY = min(mMax.mFy, p.mMax.mFy);
			float fMaxZ = min(mMax.mFz, p.mMax.mFz);

			Point pivot(fMinX, fMinY, fMinZ);
			tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
			tmp.mBenable = true;
		}
		return tmp;
	}
	Box operator -(Point& p) {
		return Box(mFx - p.mFx, mFy - p.mFy, mFz - p.mFz, mFwidth, mFheight, mFdepth);
	}
	Box operator *(float f) {
		if (f <= 0.0001f) return *this;
		return Box(mFx * f, mFy * f, mFz * f, mFwidth, mFheight, mFdepth);
	}
	Box operator /(float f) {
		if (f <= 0.0001f) return *this;
		return Box(mFx / f, mFy / f, mFz / f, mFwidth, mFheight, mFdepth);
	}


	void Set(float w, float h, float d) {
		mFwidth = w;
		mFheight = h;
		mFdepth = d;
		mHalf = { w * 0.5f, h * 0.5f, d * 0.5f };
		mPoint[0] = { mFx, mFy, mFz };
		mPoint[1] = { mFx + w, mFy, mFz };
		mPoint[2] = { mFx + w, mFy + h, mFz };
		mPoint[3] = { mFx, mFy + h, mFz };

		mPoint[4] = { mFx, mFy, mFz + d };
		mPoint[5] = { mFx + w, mFy, mFz + d };
		mPoint[6] = { mFx + w, mFy + h, mFz + d };
		mPoint[7] = { mFx, mFy + h, mFz + d };

		mMin = mPoint[0];
		mMax = mPoint[6];
		mCenter = (mMin + mMax) * 0.5f;
	}

	void Set(float x, float y, float z, float w, float h, float d) {
		mFx = x;
		mFy = y;
		mFz = z;
		v = { x, y, z };
		s = { w, h, d };

		Set(w, h, d);
	}

	void Set(Point p, float w, float h, float d) {
		v = { p.mFx, p.mFy, p.mFz };
		s = { w, h, d };

		mFx = p.mFx;
		mFy = p.mFy;
		mFz = p.mFz;
		Set(w, h, d);
	}

	bool ToBox(Box& p) {
		Box tmp = (*this) + p;
		
		if (tmp.mFx - (mFwidth + p.mFwidth) < 0.0001f
			&& tmp.mFy - (mFheight + p.mFheight) < 0.0001f
			&& tmp.mFz - (mFdepth + p.mFdepth) < 0.0001f)
		{
			return true;
		}
		return false;
	}


	Box(Point p, float w, float h, float d)
	{
		Set(p.mFx, p.mFy, p.mFz, w, h, d);
	}

	Box(float x, float y, float z, float w, float h, float d)
	{
		Set(x, y, z, w, h, d);
	}

	Box() = default;
};