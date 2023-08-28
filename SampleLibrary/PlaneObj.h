#pragma once
#include "stdafx.h"
#include "Object.h"

class PlaneObj : public Object
{
public:
	virtual bool CreateVertexBuffer() override;
	virtual bool Frame();
};

