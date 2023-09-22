#include "Sample.h"
#include "ICoreStd.h"



float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;



bool Sample::Init()
{
	m_pTex = I_Tex.Load(L"../../res/000.jpg");

	SMapDesc info = {
		129,129,1,
		L"../../res/topdownmap.jpg",
		L"../../res/shader/DefaultObj.hlsl"
	};
	

	_map = new HeightMap;

	_map->Set(m_pDevice, m_pImmediateContext);
	//_map->Load(info);
	_map->CreateHeightMap(L"../../res/topdownmap.jpg");
	_map->LoadHeightMap(L"../../res/topdownmap.jpg", L"HeightMap.hlsl");

	m_pQuadTree = std::make_shared<SQuadTree>();
	m_pQuadTree->Build(_map);

	m_pDebugCamera = std::make_shared<SDebugCamera>();
	m_pDebugCamera->Init();

	m_pDebugCamera->CreatePerspectiveFov(PI * 0.25, (float)g_dwWindowHeight / (float)g_dwWindowHeight,
		1.f, 300.f);
	m_pDebugCamera->CreateLookAt({ 0,100,-1 }, { 0,0,0 });

	ICore::g_pMainCamera = m_pDebugCamera.get();

	/*m_pMainCamera->CreateLookAt({ 0,300.f,-1.f }, { 0,0,0 });

	m_pMainCamera->CreatePerspectiveFov(PI * 0.25, (float)g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.0f);*/

	return true;
}
bool Sample::Frame()
{
	_map->Frame();
	return true;
}
bool Sample::Render()
{
	TMatrix matWorld;
	_map->SetMatrix(&matWorld,
		&ICore::g_pMainCamera->m_matView,
		&ICore::g_pMainCamera->m_matProj);
	_map->Render();

	
	TMatrix matWorld2;
	matWorld2._42 = -10.f;
	_map->SetMatrix(&matWorld2,
		&ICore::g_pMainCamera->m_matView,
		&ICore::g_pMainCamera->m_matProj);
	_map->PreRender();
	m_pTex->Apply(m_pImmediateContext, 0);
	_map->PostRender();
	return true;
}
bool Sample::Release()
{
	m_pDebugCamera->Release();
	if(_map) _map->Release();
	delete _map;
	return true;
}
bool Sample::DeleteDxResource()
{
	Core::DeleteDxResource();
	return true;
}

bool Sample::CreateDxResource()
{
	ICore::g_pMainCamera->CreatePerspectiveFov(PI * 0.25, (float)g_dwWindowWidth / (float)g_dwWindowHeight,
		1.f, 300.f);
	Core::CreateDxResource();
	return true;
}

GAME(L"kgca", 800, 600)