#pragma once
#include "Utils.h"
#include "Math.h"

// why Object has Utils?
// Object has Box, Point etc

class Object
{
public:
	int iObjIndex = -1;
	std::wstring wsName;
	Box mBox;


	virtual void SetBox(Vector3& vPos, float w, float h, float d);
	virtual void Move(float fSPF) = 0;
	virtual void SetTarget(Vector3& vTarget) = 0;


	// What Object has i need?
};


class StaticObject : Object
{
public:

	void Move(float fSPF) override {};
	void SetTarget(Vector3& vTarget) override {};

};

class DynamicObject : Object
{
public:
	Vector3 mTarget;
	Vector3 mDirection;
	float fSpeed = 100.0f;

	void Move(float fSPF) override;
	void SetTarget(Vector3& vTarget) override;
};