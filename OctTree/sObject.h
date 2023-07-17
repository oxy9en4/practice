#pragma once
#include "sColision.h"

class sObject
{
public:
	std::wstring csName;
	sPoint		 Position;
	sRect		 rect;
	virtual void SetRect(sPoint& c, float w, float h);
	virtual void Move(float fSecond) {};
	virtual void SetTarget(sPoint& t) {};
};


class sStaticObject : public sObject
{
public:
	void Move() {};
};

class sDynamicObject : public sObject {
public:
	float fSpeed = 100.0f;
	sPoint Direction;
	sPoint Target;
	void SetTarget(sPoint& t);
	void Move(float fSecond);
	sDynamicObject() {
		Direction.x = 0.0f;
		Direction.y = 0.0f;
	}
};