#pragma once
class sTimer
{
public:
	float _fGameTimer;
	float _fSPF;
	DWORD _dwBeforeTime;
	float _fAccumulatedSecond;
	int _iFPS;

	int getFPS();
	
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

