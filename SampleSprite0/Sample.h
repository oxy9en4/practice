#pragma once
#include "Core.h"
#include "PlaneObj.h"
class Sample : public Core
{
	Object* m_pMapObj = nullptr;
	Object* m_pSpriteObj = nullptr;
	std::vector<const Texture*>  m_pTexList;
	int  m_iTexIndex = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

