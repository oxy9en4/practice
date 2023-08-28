#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>

#include <map>
#include <unordered_map>
#include <assert.h>
#include <queue>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "DirectXTex.h"
#include "Math.h"

#pragma comment (lib, "d3d11.lib") // 
#pragma comment (lib, "dxgi.lib") // 
#pragma comment (lib, "d3dcompiler.lib") // 
#pragma comment (lib, "DirectXTex.lib")
#pragma comment (lib, "winmm.lib") // used for timeGetTime()
#pragma comment (lib, "BasisLib.lib")


#define randstep(fmin, fmax) ((float)fmin + ((float)fmax - (float)fmin) * rand() / RAND_MAX)
// Define a macro to start the game loop
#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) { Sample win;
#define GAME_REGISTER	win.SetRegisterClassWindow(hInstance);	// Define a macro to register the window class
#define GAME_WINDOW(s, w, h) win.SetWindow(L#s, w, h);			// Define a macro to set up the game window
#define GAME_RUN win.Run();										// Define a macro to Run the game loop
#define GAME_END return 0; };									// Define a macro to end the game loop and return

#define PI (3.141592f)
#define EPSILON ( 0.0001f)
#define RadianToDegree(radian) ( radian *( 180.0f / PI))
#define DegreeToRadian(degree) ( degree *( PI / 180.0f))

// Define a macro to set up and run the game loop with window title, width and height
#define GAME(s, w, h) GAME_START;GAME_REGISTER;GAME_WINDOW(s,w,h);GAME_RUN;GAME_END;

static float g_fMapSizeX = 3000.0f;
static float g_fMapSizeY = 3000.0f;

static void DebugString(const WCHAR* msg)
{
#ifdef _DEBUG
	OutputDebugString(msg);
#endif
}
extern HWND g_hWnd;
extern float g_fGameTimer;
extern float g_fSPF;
