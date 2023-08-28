#pragma once
#include "PlaneObj.h"

class NpcObj : public PlaneObj
{
	Vector3 m_vDirection = { 1, 1, 0 };
public:
	void Move(float fSecond);
	virtual bool Frame();
	NpcObj();
	virtual ~NpcObj();
};

