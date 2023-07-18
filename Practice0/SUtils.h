#pragma once

struct SPoint
{
	float x = 0;
	float y = 0;

	SPoint operator +(SPoint& p)
	{
		return SPoint(x + p.x, y + p.y);
	}
	SPoint operator -(SPoint& p) {
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

	float GetDistance()
	{
		return sqrt(x * x + y * y);
	}
	static float GetDistance(SPoint& p) {
		return sqrt(p.x * p.x + p.y * p.y);
	}

	SPoint() = default;
	SPoint(float x, float y) : x(x), y(y) {}
};

struct SRect {
	float mFx = 0;
	float mFy = 0;
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
		float minX = min(mMin.x, p.mMin.x);
		float minY = min(mMin.y, p.mMin.y);
		float maxX = max(mMax.x, p.mMax.x);
		float maxY = max(mMax.y, p.mMax.y);
		tmp.Set(minX, minY, maxX, maxY);
		return tmp;
	}
	void Set(SPoint& p) {
		v = { p.x, p.y };
		s = { mFWidth, mFHeight };
		mFx = p.x;
		mFy = p.y;
		Set(mFWidth, mFHeight);
	}
	void Set(float w, float h) {
		mFWidth = w;
		mFHeight = h;
		mHalf = { mFWidth * 0.5f, mFHeight * 0.5f };
		mPoint[0] = { mFx, mFy };
		mPoint[1] = { mFx + mFWidth, mFy };
		mPoint[2] = { mFx + mFWidth, mFy + mFHeight };
		mPoint[3] = { mFx, mFy + mFHeight };
		mCenter = (mPoint[0] + mPoint[2]) * 0.5f;
		mMin = mPoint[0];
		mMax = mPoint[2];
	}
	void Set(SPoint& p, float w, float h) {
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

	bool ToRect(SRect& a) {
		float minX = max(mMin.x, a.mMin.x);
		float minY = max(mMin.y, a.mMin.y);
		float maxX = min(mMax.x, a.mMax.x);
		float maxY = min(mMax.y, a.mMax.y);
		if (minX > maxX || minY > maxY) return false;
		return true;
	}
	bool RectToRect(SRect& a, SRect& b) {
		float minX = max(a.mMin.x, b.mMin.x);
		float minY = max(a.mMin.y, b.mMin.y);
		float maxX = min(a.mMax.x, b.mMax.x);
		float maxY = min(a.mMax.y, b.mMax.y);
		if (minX > maxX || minY > maxY) return false;
		return true;
	}
	
	SRect() = default;
	SRect(float x, float y, float w, float h)
	{
		Set(x, y, w, h);
	}
};

class SUtils
{
};

