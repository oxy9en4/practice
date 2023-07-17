#pragma once
#include "sColision.h"

class sObject
{
public:
	std::wstring csName;
	sPoint		 Position;
	virtual void Move() {};
	virtual void SetTarget(sPoint& t) {};
};


class sStaticObject : public sObject
{
public:
	void Move() {};
};

class sDynamicObject : public sObject {
public:
	float fSpeed = 30.0f;
	sPoint Direction;
	sPoint Target;
	void SetTarget(sPoint& t) {
		Target = t;
		Direction = Target - Position;
		float fDistacne = Direction.getDistance();
		Direction /= fDistacne; // Á¤±ÔÈ­
	}
	void Move() {
		sPoint vDir = Target - Position;
		float fD = vDir.getDistance();
		if (fD > 50.0f) {
			sPoint vVelocity = Direction * fSpeed;
			Position += vVelocity;
		}
	}
	sDynamicObject() {
		Direction.x = 0.0f;
		Direction.y = 0.0f;
	}
};