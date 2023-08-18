#pragma once
#include "Device.h"

class Core : public Device
{
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

