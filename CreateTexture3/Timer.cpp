#include "stdafx.h"
#include "Timer.h"
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
    std::cout << "[FPS]" << GetFPS() << "[GT]" << g_fGameTimer << " [SPF]" << g_fSPF << std::endl;
    return true;
}

bool Timer::Release()
{
    return true;
}
