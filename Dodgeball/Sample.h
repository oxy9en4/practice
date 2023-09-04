#pragma once
#include "Core.h"
#include "mainchar.h"
#include "bullet.h"



class Sample : public Core
{
	std::vector<const Texture*>  m_pTexList;
	int  m_iTexIndex = 0;


	using sPlaneObj = std::unique_ptr<PlaneObj>;
	using sMainchar = std::unique_ptr<mainchar>;
	using sBullet = std::unique_ptr<bullet>;
	sPlaneObj  m_pMapObj = nullptr;
	sMainchar Player = nullptr;
	sBullet   Bullet = nullptr;

	std::map<int, SpriteObj*>	m_SpriteList;
	int   m_iSpriteIndex = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

