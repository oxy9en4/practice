#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <codecvt>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <cmath>

#include <map>
#include <unordered_Map>
#include <queue>
#include <array>
#include <list>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "DirectXTex.h"
#include "Utils.h"
#include <wrl.h>

#pragma comment (lib, "d3d11.lib") // 
#pragma comment (lib, "dxgi.lib") // 
#pragma comment (lib, "d3dcompiler.lib") // 
#pragma comment (lib, "DirectXTex.lib")
#pragma comment (lib, "winmm.lib") // used for timeGetTime()
//#pragma comment (lib, "BasisLib.lib")

using namespace Microsoft::WRL;

// Define a macro to start the game loop
#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) { Sample win;
#define GAME_REGISTER	win.SetRegisterClassWindow(hInstance);	// Define a macro to register the window class
#define GAME_WINDOW(s, w, h) win.SetWindow(L#s, w, h);			// Define a macro to set up the game window
#define GAME_RUN win.Run();										// Define a macro to Run the game loop
#define GAME_END return 0; };									// Define a macro to end the game loop and return


// Define a macro to set up and run the game loop with window title, width and height
#define GAME(s, w, h) GAME_START;GAME_REGISTER;GAME_WINDOW(s,w,h);GAME_RUN;GAME_END;


typedef std::basic_string<TCHAR>			T_STR;
typedef std::basic_string<wchar_t>			W_STR;
typedef std::basic_string<char>				C_STR;
typedef std::vector<T_STR>					T_STR_VECTOR;
typedef std::basic_string<TCHAR>::iterator		T_ITOR;
typedef std::basic_string<wchar_t>::iterator	W_ITOR;
typedef std::basic_string<char>::iterator	C_ITOR;
typedef std::vector<T_STR>				T_ARRAY_ITOR;
typedef std::vector<DWORD>				DWORD_VECTOR;
typedef	std::vector< DWORD >::iterator	DWORD_VECTOR_ITOR;
typedef std::list<DWORD>				DWORD_LIST;
typedef std::list<DWORD>::iterator		DWORD_LIST_ITOR;
typedef std::list< HANDLE >				HANDLE_LIST;
typedef	std::list< HANDLE >::iterator	HANDLE_LIST_ITOR;


extern float g_fMapHalfSizeX;
extern float g_fMapHalfSizeY;
extern DWORD g_dwWindowWidth;
extern DWORD g_dwWindowHeight;

static std::wstring mtw(std::string str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(str);
}

static std::string wtm(std::wstring str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(str);
}

static void DebugString(const WCHAR* msg)
{
#ifdef _DEBUG
	OutputDebugString(msg);
#endif
}
extern HWND g_hWnd;
extern float g_fGameTimer;
extern float g_fSPF;
