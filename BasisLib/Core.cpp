#include "Core.h"
#include "ICoreStd.h"

void  Core::CreateBlendState()
{
    // alpha blending
    D3D11_BLEND_DESC bsd;
    ZeroMemory(&bsd, sizeof(bsd));
    bsd.RenderTarget[0].BlendEnable = true;
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    // 알파블랜딩 공식 - 소스(float4(0,1,0,0.5f)), 대상(1,0,0,1)
    //finalcolor(RGB) = SrcColor* SrcBlend   + DestColor*DestBlend
    //           = Scrcolor* alphaValue + DestColor * (1.0f-alphaValue)
    //           = 0,1,0 * 0.5f + 1,0,0 * (1.0f-0.5f)
    // //        만약 t= 0.0f; 결과 => 배경만 나온다.
    // //        만약 t= 1.0f; 결과 => 소스만 나온다.
    //           만약 t= 0.5f; 결과 - >소스컬러*0.5 + 배경컬러*0.5f
    //           = 0,1,0 * t + 1,0,0 * (1.0f-t)
    //           =  r*t,b*t,b*t + r*(1.0f-t),b*(1.0f-t),b*(1.0f-t)

    // (A)
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_pDevice->CreateBlendState(&bsd, &m_AlphaBlend);
}
bool  Core::Init() { return true; }
bool  Core::Frame() { return true; }
bool  Core::Render() { return true; }
bool  Core::Release() { return true; }
bool  Core::EngineInit()
{
    Device::Init();
    CreateBlendState();

    ICore::g_pDevice = m_pDevice;
    ICore::g_pContext = m_pImmediateContext;

    I_Tex.Set(m_pDevice, m_pImmediateContext);
    I_Shader.Set(m_pDevice, m_pImmediateContext);

    m_GameTimer.Init();
    Input::GetInstance().Init();

    m_pMainCamera = std::make_shared<TCamera>();
    m_pMainCamera->Init();

    I_Writer.Init();
    if (m_pSwapChain)
    {
        IDXGISurface1* pBackBuffer;
        HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
            (LPVOID*)&pBackBuffer);
        if (SUCCEEDED(hr))
        {
            I_Writer.Create(pBackBuffer);
        }
        if (pBackBuffer) pBackBuffer->Release();
    }

    Init();
    return true;
}
bool  Core::EngineFrame()
{
    m_GameTimer.Frame();
    Input::GetInstance().Frame();
    //m_pMain
    ICore::g_pMainCamera->Frame();
    //Core::m_pMainCamera->Frame();
    Device::Frame();
    I_Writer.Frame();
    //I_Sound.Frame();
    Frame();
    return true;
}
bool  Core::EngineRender()
{
    Device::PreRender();
    m_pImmediateContext->OMSetBlendState(m_AlphaBlend, 0, -1);

    Render();

    m_pMainCamera->Render();
    m_GameTimer.Render();
    Input::GetInstance().Render();

    I_Writer.Render();
    Device::PostRender();
    return true;
}
bool  Core::EngineRelease()
{
    Release();

    if (m_AlphaBlend)m_AlphaBlend->Release();
    m_GameTimer.Release();
    Input::GetInstance().Release();
    m_pMainCamera->Release();
    I_Writer.Release();
    Device::Release();
    return true;
}
bool Core::Run()
{
    EngineInit();
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 게임로직을 처리
            if (!EngineFrame() || !EngineRender())
            {
                break;
            }
        }
    }
    EngineRelease();
    return true;
}

bool Core::DeleteDxResource()
{
    I_Writer.DeleteDxResource();
    return true;
}

bool Core::CreateDxResource()
{
    if (m_pSwapChain)
    {
        IDXGISurface1* pBackBuffer;
        HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
            (LPVOID*)&pBackBuffer);
        if (SUCCEEDED(hr))
        {
            I_Writer.CreateDxResource(pBackBuffer);
        }
        if (pBackBuffer) pBackBuffer->Release();
    }
    return false;
}
