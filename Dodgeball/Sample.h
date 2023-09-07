#pragma once
#include "Core.h"
#include "npc.h"




class Sample : public Core
{
	std::vector<const Texture*>  m_pTexList;
	int  m_iTexIndex = 0;


	using sPlaneObj = std::unique_ptr<PlaneObj>;
	using sMainchar = std::unique_ptr<mainchar>;
	using sNpc = std::unique_ptr<npc>;

	sPlaneObj  m_pMapObj = nullptr;
	sMainchar Player = nullptr;
	sMainchar PlayerDeath = nullptr;
	sNpc Npc = nullptr;


	std::map<int, SpriteObj*>	m_SpriteList;
	int   m_iSpriteIndex = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

