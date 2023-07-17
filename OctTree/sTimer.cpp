#include "stdafx.h"
#include "sTimer.h"



bool sTimer::Init(){
	_fAccumulatedSecond = 0.0f;
	_fSPF = 0.0f;
	_fGameTimer = 0.0f;
	_dwBeforeTime = timeGetTime(); // tick counter 1000 => 1sec
	return true;
}
bool sTimer::Frame() {
	DWORD dwCurrentTime = timeGetTime();
	DWORD dwElapseTime = dwCurrentTime - _dwBeforeTime;
	_fSPF = dwElapseTime / 1000.0f;
	_fGameTimer += _fSPF;
	_dwBeforeTime = dwCurrentTime;

	_fAccumulatedSecond += _fSPF;
	return true;
}

int sTimer::getFPS() {
	static int iFPS = 0;
	if (_fAccumulatedSecond >= 1.0f) {
		_iFPS = iFPS;
		iFPS = 0;
		_fAccumulatedSecond -= 1.0f;
	}
	++iFPS;
	return _iFPS;
}


bool sTimer::Render() {
	std::cout << "[FPS]" << getFPS() << "[GT]" << _fGameTimer << "[SPF]" << _fSPF << std::endl;
	return true;
}
bool sTimer::Release() {
	return true;
}