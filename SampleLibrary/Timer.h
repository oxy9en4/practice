#pragma once
#include "stdafx.h"

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

