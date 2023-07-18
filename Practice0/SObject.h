#pragma once
#include "SUtils.h"
class SObject
{
public:
	std::wstring mName;
	SPoint		 mPivot;
	SRect		 mCollisionBox;
	virtual void SetRect(SPoint& p, float w, float h);
	virtual void SetTarget(SPoint& p) {};
	virtual void Move(float fSecond) {};
};

class SStaticObject : public SObject {
public:
	void Move(float fSecond) {};
};

class SDynamicObject : public SObject {
public:
	float mFspeed = 100.0f;
	SPoint mTarget;
	SPoint mDirection;

	void SetTarget(SPoint& p);
	void Move(float fSecond);

	
};

