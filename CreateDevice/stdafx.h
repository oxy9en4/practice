#pragma once
#include <Windows.h>
#include <string>
#include <assert.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>



#pragma comment (lib, "d3d11.lib") // 
#pragma comment (lib, "dxgi.lib") // 
#pragma comment (lib, "d3dcompiler.lib") // 


// Define a macro to start the game loop
#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) { Sample win;
#define GAME_REGISTER	win.SetRegisterClassWindow(hInstance);	// Define a macro to register the window class
#define GAME_WINDOW(s, w, h) win.SetWindow(L#s, w, h);			// Define a macro to set up the game window
#define GAME_RUN win.Run();										// Define a macro to Run the game loop
#define GAME_END return 0; };									// Define a macro to end the game loop and return

// Define a macro to set up and run the game loop with window title, width and height
#define GAME(s, w, h) GAME_START;GAME_REGISTER;GAME_WINDOW(s,w,h);GAME_RUN;GAME_END;