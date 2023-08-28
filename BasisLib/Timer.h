#pragma once
#include "std.h"

class Timer
{
public:
	DWORD mdwBeForeTime;
	float mfAccumulatedSecond;
	int miFPS;

	int GetFPS();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};

