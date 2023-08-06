#pragma once
#include "Utils.h"



// why Object has Utils?
// Object has Box, Point etc

class Object
{
public:
	int iNodeIndex = -1;
	std::wstring wsName;
	Box mBox;
	int iListIndex = -1;


	virtual void SetBox(Vector3& vPos, float w, float h, float d);
	virtual void Move(float fSPF) {};
	virtual void SetTarget(Vector3& vTarget) {};


	// What Object has i need?
};


class StaticObject : public Object
{
public:

	void Move(float fSPF) override {};
	void SetTarget(Vector3& vTarget) override {};

};

class DynamicObject : public Object
{
public:
	Vector3 mTarget;
	Vector3 mDirection;
	float fSpeed = 100.0f;

	void Move(float fSPF) override;
	void SetTarget(Vector3& vTarget) override;
};