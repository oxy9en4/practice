#include "Sample.h"

Vector3 posPlayer;
float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{
	// map
	m_pMapObj = std::make_unique<PlaneObj>();
	m_pMapObj->Set(m_pDevice, m_pImmediateContext);
	m_pMapObj->SetPos({ 0.0f,0.0f ,0.0f });
	m_pMapObj->SetScale(Vector3(g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f));
	m_pMapObj->Create(L"../../res/topdownmap.jpg", L"../../res/shader/Plane.hlsl");

	//player
	Player = std::make_unique<mainchar>();
	Player->Init();
	SpriteInfo info;
	info.iNumRow = 9;
	info.iNumColumn = 16;
	info.fAnimTimer = 10.0f;
	info.p = { 0.0f, 0.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar.png";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	Player->Load(m_pDevice, m_pImmediateContext, info);

	PlayerDeath = std::make_unique<mainchar>();
	PlayerDeath->Init();
	info.Reset();
	info.iNumRow = 7;
	info.iNumColumn = 11;
	info.fAnimTimer = 10.0f;
	info.p = { 0.0f, 0.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar_death.dds";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	PlayerDeath->Load(m_pDevice, m_pImmediateContext, info);
	PlayerDeath->m_State = 0;
	m_SpriteList.insert(std::make_pair(m_iSpriteIndex++, PlayerDeath.get()));

	Npc = std::make_unique<npc>();
	Npc->Init();

	info.Reset();
	info.iNumRow = 9;
	info.iNumColumn = 16;
	info.fAnimTimer = 10.0f;
	info.p = { 200.0f, 200.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar.png";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	Npc->Load(m_pDevice, m_pImmediateContext, info);
	Npc->m_State = 0;


	// bullet
	info.Reset();
	info.iNumRow = 3;
	info.iNumColumn = 7;
	info.fAnimTimer = 5.0f;
	info.p = { 0.0f, 0.0f, 0.0f };
	info.s = Vector3(30.0f, 30.0f, 1.0f);
	info.texFile = L"../../res/bullet.png";
	info.shaderFile = L"../../res/shader/Plane.hlsl";

	Player->Bullet->Load(m_pDevice, m_pImmediateContext, info);
	m_SpriteList.insert(std::make_pair(m_iSpriteIndex++, Player->Bullet.get()));

	Npc->Bullet->Load(m_pDevice, m_pImmediateContext, info);



	m_pMainCamera->Create({ 0.0f,0.0f, 0.0f }, { (float)m_dwWindowWidth, (float)m_dwWindowHeight });
	return true;
}
bool Sample::Frame()
{
	m_pMapObj->Frame();

	if (I_Input.m_dwKeyState[VK_RBUTTON] == KEY_PUSH && Player->m_State == 0)
	{
		Vector3 mouse = I_Input.GetWorldPos(
			{ (float)g_dwWindowWidth , (float)g_dwWindowHeight },
			m_pMainCamera->m_vCameraPos);
		Player->UpdateDir(mouse);
		Player->mTarget = mouse;
		Player->m_State = 0;
		Player->m_iCurrentAnimIndex = 0;
	}
	if (I_Input.m_dwKeyState['Q'] == KEY_PUSH
		&& Player->m_State == 0
		&& Player->Bullet->visible == false)
	{
		Vector3 mouse = I_Input.GetWorldPos(
			{ (float)g_dwWindowWidth , (float)g_dwWindowHeight },
			m_pMainCamera->m_vCameraPos);
		
		Player->Bullet->m_vPos = Player->m_vPos;
		Player->Bullet->UpdateDir(mouse);
		Player->Bullet->mTarget = Player->Bullet->m_vPos;

		Player->UpdateDir(mouse);
		Player->mTarget = Player->m_vPos;
		Player->m_State = 1;
		Player->m_iCurrentAnimIndex = 0;

	}
	if (I_Input.m_dwKeyState['S'] == KEY_PUSH && Player->m_State == 1)
	{
		Player->m_State = 3;
		Player->m_iCurrentAnimIndex = Player->m_AttackList.size() - 1;
		Player->mTarget = Player->m_vPos;
	}
	if (I_Input.m_dwKeyState['D'] == KEY_PUSH && Player->m_State == 0)
	{
		Vector3 mouse = I_Input.GetWorldPos(
			{ (float)g_dwWindowWidth , (float)g_dwWindowHeight },
			m_pMainCamera->m_vCameraPos);
		Player->UpdateDir(mouse);
		Player->mTarget = mouse;
		Player->m_State = 2;
		Player->m_iCurrentAnimIndex = 0;
	}
	posPlayer = Player->m_vPos;
	Npc->Frame();
	Player->Frame();
	return true;
}

bool Sample::Render()
{
	m_pMapObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	m_pMapObj->Render();

	Player->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Player->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Player->Render();

	Npc->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Npc->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Npc->Render();
	return true;
}
bool Sample::Release()
{
	m_pMapObj->Release();
	//m_pSpriteTexObj->Release();
	Player->Release();
	Player->Bullet->Release();
	//m_pSpriteAirObj->Release();
	Npc->Release();
	Npc->Bullet->Release();
	return true;
}

GAME(L"kgca", 800, 600)