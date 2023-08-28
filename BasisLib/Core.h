#pragma once
#include "Timer.h"
#include "Camera.h"
#include "Input.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "SWriter.h"

class Core : public Device
{
public:
	Timer m_GameTimer;
	Camera m_MainCamera;
	ID3D11BlendState* m_AlphaBlend = nullptr;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	void  CreateBlendState();
	bool Run();
private:
	virtual bool EngineInit(); // Engine means private
	virtual bool EngineFrame();
	virtual bool EngineRender();
	virtual bool EngineRelease();
public:
};

