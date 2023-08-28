#include "Timer.h"
#include "SWriter.h"
float	g_fGameTimer = 0.0f;
float   g_fSPF = 0.0f;

int Timer::GetFPS()
{
    static int iFPS = 0;
    if (mfAccumulatedSecond >= 1.0f)
    {
        miFPS = iFPS;
        iFPS = 0;
        mfAccumulatedSecond -= 1.0f;
    }
    ++iFPS;
    return miFPS;
}

bool Timer::Init()
{
    mfAccumulatedSecond = 0.0f;
    g_fGameTimer = 0.0f;
    g_fSPF = 0.0f;
    mdwBeForeTime = timeGetTime();
    return true;
}

bool Timer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - mdwBeForeTime;
    g_fSPF = dwElapseTime / 1000.0f;
    g_fGameTimer += g_fSPF;
    mdwBeForeTime = dwCurrentTime;

    mfAccumulatedSecond += g_fSPF;

    return true;
}

bool Timer::Render()
{
    std::wstring msg = L"[FPS]";
    msg += std::to_wstring(GetFPS());
    msg += L"[GT]";
    msg += std::to_wstring(g_fGameTimer);
    msg += L"[SPF]";
    msg += std::to_wstring(g_fSPF);

    I_Writer.AddText(
        msg.c_str(), 0, 0,
        { 1.0f , 1.0f, 0.0f, 1.0f } );
    
    return true;
}

bool Timer::Release()
{
    return true;
}
