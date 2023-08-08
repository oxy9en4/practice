#pragma once
#include "Core.h"

class Sample : public Core
{
	IDXGISwapChain*			m_pSwapChain = nullptr;
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};