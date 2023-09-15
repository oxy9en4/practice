#include "Sample.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;



bool Sample::Init()
{
	_map = new HeightMap;

	_map->Set(m_pDevice, m_pImmediateContext);
	_map->CreateHeightMap(L"../../res/topdownmap.jpg");
	_map->LoadHeightMap(L"../../res/topdownmap.jpg", L"HeightMap.hlsl");
	
	m_pMainCamera->CreateLookAt({ 0,300.f,-1.f }, { 0,0,0 });

	m_pMainCamera->CreatePerspectiveFov(PI * 0.25, (float)g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.0f);
	return true;
}
bool Sample::Frame()
{
	DebugMode();
	//_map->Frame();
	return true;
}
bool Sample::Render()
{
	_map->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matPerspectiveProj);
	_map->Render();
	return true;
}
bool Sample::Release()
{

	_map->Release();
	delete _map;
	return true;
}

void Sample::DebugMode()
{
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD4] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD5] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	}
}

GAME(L"kgca", 800, 600)