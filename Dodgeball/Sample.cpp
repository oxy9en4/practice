#include "Sample.h"

Vector3 posPlayer;
float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{
	
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<npc> tmp = std::make_shared<npc>();
		npcList.push_back(tmp);
	}
	deathSound = I_Sound.Load(L"../../res/Damage.mp3");
	BGM = I_Sound.Load(L"../../res/Remix.mp3");
	
	BGM->VolumeDown();
	BGM->Play();

	// map
	m_pMapObj = std::make_unique<PlaneObj>();
	m_pMapObj->Set(m_pDevice, m_pImmediateContext);
	m_pMapObj->SetPos({ 0.0f,0.0f ,0.0f });
	m_pMapObj->SetScale(Vector3(g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f));
	m_pMapObj->Create(L"../../res/Ground.jpg", L"../../res/shader/Plane.hlsl");

	//player
	Player = std::make_unique<mainchar>();
	Player->Init();
	SpriteInfo info;
	info.iNumRow = 9;
	info.iNumColumn = 16;
	info.fAnimTimer = 10.0f;
	info.p = { -200.0f, -200.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar.png";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	Player->Load(m_pDevice, m_pImmediateContext, info);
	Player->mTarget = Player->m_vPos;
	Vector2 tmp = { -200.0f, -200.0f};
	Player->SetRect( tmp, 50.0f, 50.0f);
	


	PlayerDeath = std::make_unique<mainchar>();
	PlayerDeath->Init();
	info.Reset();
	info.iNumRow = 7;
	info.iNumColumn = 11;
	info.fAnimTimer = 1.0f;
	info.p = { 0.0f, 0.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar_death.dds";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	PlayerDeath->Load(m_pDevice, m_pImmediateContext, info);
	PlayerDeath->m_State = -1;
	m_SpriteList.insert(std::make_pair(m_iSpriteIndex++, PlayerDeath.get()));

	for (int i = 0; i < npciNum; i++)
	{
		npcList[i] = std::make_unique<npc>();
		npcList[i]->Init();
	}
	/*Npc = std::make_unique<npc>();
	Npc->Init();
	Npc2 = std::make_unique<npc>();
	Npc2->Init();*/

	info.Reset();
	info.iNumRow = 9;
	info.iNumColumn = 16;
	info.fAnimTimer = 10.0f;
	info.p = { 200.0f, 200.0f, 0.0f };
	info.s = Vector3(100.0f, 100.0f, 1.0f);
	info.texFile = L"../../res/mainchar.png";
	info.shaderFile = L"../../res/shader/Plane.hlsl";
	tmp = { 200.0f, 200.0f };
	for (int i = 0; i < npciNum; i++)
	{
		info.p = { 200.0f - i * 100.0f, 200.0f, 0.0f };
		tmp = { (200.0f - i * 100.0f), 200.0f };
		npcList[i]->Load(m_pDevice, m_pImmediateContext, info);
		npcList[i]->m_State = 0;
		npcList[i]->SetRect(tmp, 50.0f, 50.0f);
	}

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
	tmp = { 3000.0f, 3000.0f };
	for (int i = 0; i < npciNum; i++)
	{
		npcList[i]->Bullet->Load(m_pDevice, m_pImmediateContext, info);
		npcList[i]->Bullet->SetRect(tmp, 10.0f, 20.0f);

	}
	/*Npc->Bullet->Load(m_pDevice, m_pImmediateContext, info);
	Npc2->Bullet->Load(m_pDevice, m_pImmediateContext, info);
	Npc->Bullet->SetRect(tmp, 10.0f, 20.0f);
	Npc2->Bullet->SetRect(tmp, 10.0f, 20.0f);*/
	Player->Bullet->SetRect(tmp, 10.0f, 20.0f);
	m_pMainCamera->Create({ 0.0f,0.0f, 0.0f }, { (float)m_dwWindowWidth, (float)m_dwWindowHeight });
	return true;
}
bool Sample::Frame()
{
	D2D1::ColorF color = {0,0,0,1};
	SWriter::GetInstance().AddText(L"Q : 공격\nS : 캔슬\nD : 회피\nR : 재시작", 0, 100, color);

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

		for (int i = 0; i < npciNum; i++)
		{
			if (npcList[i]->m_State != -1)
			{
				npcList[i]->m_State = CHAR_DODGE;
				npcList[i]->isMoving = false;
				npcList[i]->isAttacking = false;
				npcList[i]->isDodging = true;
			}
		}
		/*Npc->m_State = CHAR_DODGE;
		Npc->isMoving = false;
		Npc->isAttacking = false;
		Npc->isDodging = true;*/
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
	if (I_Input.m_dwKeyState['R'])
	{
		Init();
	}
	posPlayer = Player->m_vPos;

	for (int i = 0; i < npciNum - 1; i++)
	{
		for (int j = i + 1; j < npciNum; j++)
		{
			if (npcList[i]->m_RT.ToRect(npcList[j]->m_RT) 
				&& npcList[i]->m_State != -1
				&& npcList[j]->m_State != -1)
			{
				Vector3 temp;
				temp = npcList[i]->mDir * -0.005f;
				npcList[i]->m_vPos = npcList[i]->m_vPos + temp;
				npcList[j]->m_vPos = npcList[j]->m_vPos - temp;
				npcList[i]->m_State = 0;
				npcList[j]->m_State = 0;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (npcList[i]->m_State != -1)
			npcList[i]->Frame();

	}
	/*Npc->Frame();
	Npc2->Frame();*/
	Player->Frame();

	for (int i = 0; i < npciNum; i++)
	{


		if (PlayerCollisionCheck() && Player->m_State != -1)
		{
			Player->m_State = -1;
			npcList[i]->Bullet->visible = false;
			Vector2 tmp = { 3000.0f, 3000.0f };
			npcList[i]->Bullet->SetRect(tmp, 0.0f, 0.0f);
			deathSound->PlayEffect();
			deathSound->VolumeDown();
		}

		if (NpcCollisionCheck(i) && npcList[i]->m_State != -1)
		{
			npcList[i]->m_State = -1;
			Player->Bullet->visible = false;
			Vector2 tmp = { 3000.0f, 3000.0f };
			Player->Bullet->SetRect(tmp, 0.0f, 0.0f);
			deathSound->PlayEffect();
			deathSound->VolumeDown();
		}
	}
	return true;

}

bool Sample::Render()
{

	m_pMapObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	m_pMapObj->Render();

	Player->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Player->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	if (Player->m_State >= 0)
	{
		Player->Render();
	}
	else
	{
		PlayerDeath->Frame();
		PlayerDeath->m_vPos = Player->m_vPos;
		PlayerDeath->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
		PlayerDeath->Render();
	}
	for (int i = 0; i < npciNum; i++)
	{

		npcList[i]->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
		npcList[i]->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);

		if (npcList[i]->m_State >= 0)
		{
			npcList[i]->Render();
		}

		else
		{
			PlayerDeath->Frame();
			PlayerDeath->m_vPos = npcList[i]->m_vPos;
			PlayerDeath->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
			PlayerDeath->Render();
		}

	}
	/*Npc->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Npc->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Npc2->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);
	Npc2->Bullet->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProj);*/


	return true;
}
bool Sample::Release()
{
	m_pMapObj->Release();
	//m_pSpriteTexObj->Release();
	Player->Release();
	Player->Bullet->Release();
	//m_pSpriteAirObj->Release();
	for (int i = 0; i < npciNum; i++)
	{
		npcList[i]->Release();
		if (npcList[i]->Bullet)
			npcList[i]->Bullet->Release();
	}
	/*Npc->Release();
	Npc->Bullet->Release();
	Npc2->Release();
	Npc2->Bullet->Release();*/
	return true;
}

bool Sample::PlayerCollisionCheck()
{
	for (int i = 0; i < npciNum; i++)
	{
		if (npcList[i]->Bullet->m_RT.ToRect(Player->m_RT))
		{
			return true;
		}
	}
	return false;
}

bool Sample::NpcCollisionCheck(int i)
{
	if (Player->Bullet->m_RT.ToRect(npcList[i]->m_RT))
	{
		return true;
	}
	return false;
}

GAME(L"kgca", 800, 600)