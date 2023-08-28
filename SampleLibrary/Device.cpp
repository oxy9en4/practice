#include "Device.h"

bool Device::Init()
{
	// 렌더링을 위한 DirectX 설정을 초기화
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.BufferDesc.Width = 800;
	SwapChainDesc.BufferDesc.Height = 600;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = m_hWnd;
	SwapChainDesc.Windowed = true;

	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT Flags = 0;
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	// 1) DirectX 디바이스와 스왑 체인을 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		DriverType,
		NULL,
		Flags,
		&pFeatureLevels, 1,
		D3D11_SDK_VERSION,
		&SwapChainDesc,

		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pImmediateContext);
	if (FAILED(hr))
	{
		return false; // 디바이스 생성이 실패하면 false 반환
	}
	// 2) get BackBuffer and
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (SUCCEEDED(hr))
	{
		// 3) Create Render Target
		hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		if (FAILED(hr))
		{
			pBackBuffer->Release();
			return false;
		}
		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	}
	pBackBuffer->Release();

	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
	return true;
}

bool Device::Frame()
{
	return true;
}

bool Device::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool Device::Release()
{
	// 자원을 해제하고 메모리 정리
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pDevice) m_pDevice->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	return true;
}


bool Device::PreRender()
{
	float color[4] = { 0.343f, 0.34522f, 0.64333f, 1 };
	// 렌더 타겟 뷰를 지정된 색상으로 지움.
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	return true;
}

bool Device::PostRender()
{
	// 지형, 캐릭터, 오브젝트, 이펙트, 인터페이스
// 스왑 체인을 통해 화면에 렌더링한 내용을 표시
	HRESULT hr = m_pSwapChain->Present(0, 0);
	if (FAILED(hr))
	{
		return false; // 스왑 체인을 통한 표시가 실패한 경우 false 반환
	}
	return true;
}

