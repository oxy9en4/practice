#pragma once
#include "stdafx.h"
#include "Window.h"

class Device : public Window
{
public:
	IDXGIFactory*			m_pGIFactory;
	IDXGISwapChain*			m_pSwapChain = nullptr;
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	D3D11_VIEWPORT			m_ViewPort;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();


	bool	PreRender();
	bool	PostRender();

};

