#include "stdafx.h"
#include "Timer.h"

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
    mfGameTimer = 0.0f;
    mfSPF = 0.0f;
    mdwBeForeTime = timeGetTime();
    return true;
}

bool Timer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - mdwBeForeTime;
    mfSPF = dwElapseTime / 1000.0f;
    mfGameTimer += mfSPF;
    mdwBeForeTime = dwCurrentTime;

    mfAccumulatedSecond += mfSPF;

    return true;
}

bool Timer::Render()
{
    std::cout << "[FPS]" << GetFPS() << "[GT}" << mfGameTimer << " [SPF]" << mfSPF << std::endl;
    return true;
}

bool Timer::Release()
{
    return true;
}
