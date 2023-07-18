#pragma once

#define randstep(fmin, fmax) ((float)fmin + ((float)fmax - (float)min)* rand() / RANDMAX)

struct SPoint
{
	float x = 0;
	float y = 0;
	SPoint operator+(SPoint& p) {
		return SPoint(x + p.x, y + p.y);
	}
	SPoint operator-(SPoint& p) {
		return SPoint(x - p.x, y - p.y);
	}
	SPoint operator*(float p) {
		return SPoint(x * p, y * p);
	}
	SPoint operator/(float p) {
		return SPoint(x / p, y / p);
	}
	SPoint& operator/=(float p) {
		x = x / p;
		y = y / p;
		return *this;
	}

	float GetDistance() {
		return sqrt(x * x + y * y);
	}
	SPoint(float x, float y) : x(x), y(y) {}
	SPoint();
};

struct SFloat2
{
	union {
		struct {
			float mFx;
			float mFy;
		};
		float v[2] = { 0 };
	};
};

struct SRect : SFloat2 {
	float mFWidth = 0;
	float mFHeight = 0;
	SPoint mPoint[4];
	SPoint mCenter;
	SPoint mHalf;
	SPoint mMin;
	SPoint mMax;
	SPoint v;
	SPoint s;
	SRect operator + (SRect& p) {
		SRect tmp;
		float newX = min(mMin.x, p.mMin.x);
		float newY = min(mMin.y, p.mMin.y);
		float maxX = max(mMax.x, p.mMax.x);
		float maxY = max(mMax.y, p.mMax.y);
		SPoint pos = { newX, newY };
		tmp.Set(pos, maxX - newX, maxY - newY);
		return tmp;
	}
	void Set(SPoint p) {
		v = { p.x, p.y };
		s = { mFWidth, mFHeight };
		mFx = p.x;
		mFy = p.y;
		Set(mFWidth, mFHeight);
	}

	void Set(float w, float h)
	{
		mFWidth = w;
		mFHeight = h;
		mHalf = { mFWidth / 2, mFHeight / 2 };
		mPoint[0] = { mFx , mFy };
		mPoint[1] = { mFx + mFWidth , mFy };
		mPoint[2] = mCenter;
		mPoint[3] = { mFx , mCenter.y };
		mCenter = (mPoint[0] + mPoint[2]) * 0.5f;
		mMin = mPoint[0];
		mMax = mPoint[2];
	}

	void Set(SPoint p, float w, float h) {
		v = { p.x, p.y };
		s = { mFWidth, mFHeight };
		mFx = p.x;
		mFy = p.y;
		Set(w, h);
	}

	void Set(float x, float y, float w, float h) {
		v = { x, y };
		s = { w, h };
		mFx = x;
		mFy = y;
		Set(w, h);
	}


	SRect();
	SRect(float x, float y, float w, float h) {
		Set(x, y, w, h);
	}
};