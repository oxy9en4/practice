#pragma once
#include "stdafx.h"
#include "Timer.h"
#include "Camera.h"
#include "Input.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "Device.h"

class Core : public Device
{
public:
	Timer m_GameTimer;
	Camera m_MainCamera;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool Run();
private:
	virtual bool EngineInit(); // Engine means private
	virtual bool EngineFrame();
	virtual bool EngineRender();
	virtual bool EngineRelease();
public:
	Core() {};
	virtual ~Core() {}
};

