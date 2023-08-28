#pragma once
#include "Core.h"
#include "Object.h"

class Sample : public Core
{
	Object* m_pMapObj = nullptr;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

