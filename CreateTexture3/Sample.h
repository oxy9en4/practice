#pragma once
#include "Core.h"
#include "Player.h"
#include "NpcObj.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"





class Sample : public Core
{
	Object* m_pMapObj = nullptr;
	Object* m_pPlayer = nullptr;
	std::vector<Object*> m_NpcList;
	ID3D11BlendState *m_AlphaBlend = nullptr;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void CreateBlendState();
};