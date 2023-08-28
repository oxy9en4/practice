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
			// Update frame and render if no messages
			if (!EngineFrame() || !EngineRender())
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
	Device::Init();
	I_Tex.Set(m_pDevice, m_pImmediateContext);
	I_Shader.Set(m_pDevice, m_pImmediateContext);
	m_GameTimer.Init();
	Input::GetInstance().Init();
	m_MainCamera.Init();
	Init();
	return true;
}

bool Core::EngineFrame()
{
	m_GameTimer.Frame();
	Input::GetInstance().Frame();
	m_MainCamera.Frame();
	Device::Frame();
	Frame();
	return true;
}

bool Core::EngineRender()
{
	Device::PreRender();
	Render();

	m_MainCamera.Render();
	m_GameTimer.Render();
	Input::GetInstance().Render();
	Device::PostRender();
	return true;
}

bool Core::EngineRelease()
{
	Release();
	m_GameTimer.Release();
	Input::GetInstance().Release();
	m_MainCamera.Release();
	Device::Release();
	return true;
}
