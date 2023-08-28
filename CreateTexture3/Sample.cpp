#include "stdafx.h" 
#include "Sample.h"

float g_fMapHalfSizeX = 400.0f;
float g_fMapHalfSizeY = 300.0f;

bool Sample::Init() {
	
	CreateBlendState();


	/*std::wstring texname[] = { 
		L"../../res/kgcabk.bmp", 
		L"../../res/ade4.dds", 
		L"../../res/bitmap1.bmp",
		L"../../res/103.tga"
	};*/

	srand(time(NULL));
	m_pMapObj = new PlaneObj;
	m_pMapObj->Set(m_pDevice, m_pImmediateContext);
	m_pMapObj->SetPos({-g_fMapHalfSizeX, 0.0f, 0.0f });
	m_pMapObj->SetScale(Vector3(g_fMapSizeX, g_fMapSizeY, 1.0f));
	
	m_pMapObj->Create(L"../../res/ground.png", L"Plane.hlsl");

	m_pPlayer = new Player;
	m_pPlayer->Set(m_pDevice, m_pImmediateContext);
	m_pPlayer->SetPos({ -g_fMapHalfSizeX, 0.0f, 0.0f });
	m_pPlayer->SetScale(Vector3(50.0f, 50.0f, 1.0f));
	Vector2 rt = { m_pPlayer->m_vPos.x, m_pPlayer->m_vPos.y };
	m_pPlayer->SetRect(rt,
						m_pPlayer->m_vScale.x * 2.0f, m_pPlayer->m_vScale.y * 2.0f);
	m_pPlayer->Create(L"../../res/blackhole2.png", L"Plane.hlsl");

	m_MainCamera.Create(m_pPlayer->m_vPos,
						{ (float)m_dwWindowWidth, (float)m_dwWindowHeight });


	for (int iObj = 0; iObj < 10; iObj++)
	{
		Object* pObj = new NpcObj;
		pObj->Set(m_pDevice, m_pImmediateContext);
		pObj->SetPos(Vector3(randstep(-g_fMapHalfSizeX, +g_fMapHalfSizeX),
							randstep(-g_fMapHalfSizeY, +g_fMapHalfSizeY), 0));
		pObj->SetScale(Vector3(50.0f, 50.0f, 1.0f));
		Vector2 rt = { pObj->m_vPos.x, pObj->m_vPos.y };
		pObj->SetRect(rt,
					pObj->m_vScale.x * 2.0f,
					pObj->m_vScale.y * 2.0f);
		pObj->Create(L"../../res/air.png", L"Plane.hlsl");
		m_NpcList.push_back(pObj);
	}
	return true;
}
bool Sample::Frame() {
	m_pPlayer->Frame();
	m_pMapObj->Frame();
	for (auto obj : m_NpcList)
	{
		if (obj->m_bDead == false)
		{
			obj->Move(g_fSPF);
			obj->Frame();
		}
	}

	for (auto obj : m_NpcList)
	{
		if (m_pPlayer->m_RT.ToRect(obj->m_RT))
		{
			obj->m_bDead = true;
		}
		float fHalfWidth = m_dwWindowWidth / 2.0f;
		float fHalfHeight = m_dwWindowHeight / 2.0f;
		
		// client
		Vector2 vMouse = { (float)I_Input.m_MousePos.x, (float)I_Input.m_MousePos.y };
		// world
		Vector2 vMouseWorldLT = { m_MainCamera.m_vCameraPos.x - fHalfWidth,
								m_MainCamera.m_vCameraPos.y + fHalfHeight };
		vMouse.x = vMouseWorldLT.x + vMouse.x;
		vMouse.y = vMouseWorldLT.y - vMouse.y;
		std::wstring msg = std::to_wstring(vMouse.x);
		msg += L",";
		msg += std::to_wstring(vMouse.y);
		msg += L"\n";
		DebugString(msg.c_str());
		if (obj->m_RT.ToPoint(vMouse))
		{
			obj->m_bDead = true;
		}
	}
	return true;
}
bool Sample::Render() {
	m_pImmediateContext->OMSetBlendState(m_AlphaBlend, 0, -1);
	m_MainCamera.m_vCameraPos = m_pPlayer->m_vPos;
	m_pMapObj->SetMatrix(nullptr, &m_MainCamera.m_matView,
									&m_MainCamera.m_matOrthoProj);
	m_pMapObj->Render();

	bool gamefinish = true;
	for (auto obj : m_NpcList)
	{
		if (obj->m_bDead == false)
		{
			obj->SetMatrix(nullptr, &m_MainCamera.m_matView,
				&m_MainCamera.m_matOrthoProj);
			obj->Render();
			gamefinish = false;
		}
	}
	m_pPlayer->SetMatrix(nullptr, &m_MainCamera.m_matView,
								&m_MainCamera.m_matOrthoProj);
	m_pPlayer->Render();
	

	return true;
}
bool Sample::Release() {
	m_pMapObj->Release();
	delete m_pMapObj;
	m_pMapObj = nullptr;

	m_pPlayer->Release();
	delete m_pPlayer;
	m_pPlayer = nullptr;
	for (auto obj : m_NpcList)
	{
		obj->Release();
		delete obj;
	}
	m_NpcList.clear();
	m_AlphaBlend->Release();
	return true;
}

void Sample::CreateBlendState()
{
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(bsd));
	bsd.RenderTarget[0].BlendEnable = true;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	m_pDevice->CreateBlendState(&bsd, &m_AlphaBlend);
}

GAME(L"KGCA", 800, 600) // 게임 진입점 및 설정을 정의하는 매크로