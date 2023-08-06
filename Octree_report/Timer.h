#pragma once
#pragma comment(lib, "winmm.lib") // used for timeGetTime()

class Timer
{
public:
	float mfGameTimer;
	float mfSPF;
	DWORD mdwBeForeTime;
	float mfAccumulatedSecond;
	int miFPS;
	
	int GetFPS();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	
};

