#include "stdafx.h"
#include "Core.h"

bool Core::Init() { return true; }

bool Core::Frame() { return true; }

bool Core::Render() { return true; }

bool Core::Release() { return true; }

bool Core::Run()
{
	EngineInit(); // Initialize the engine
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// Process window message if any
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			if (!EngineFrame() || EngineRender())
			{
				break;
			}
		}
	}
	EngineRelease(); // Release Engine resources
	return true;
}

bool Core::EngineInit()
{
	Init();
	return true;
}

bool Core::EngineFrame()
{
	Frame();
	return true;
}

bool Core::EngineRender()
{
	Render();
	return true;
}

bool Core::EngineRelease()
{
	Release();
	return true;
}
