#pragma once
#include "Core.h"
#include "Object.h"




class Sample : public Core
{
	std::vector<Object*> m_ObjList;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};