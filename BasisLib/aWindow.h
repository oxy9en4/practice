#pragma once
#include "std.h"
class Window
{
public:
	HINSTANCE	m_hInstance;                        // Variable to store the window instance 
	HWND		m_hWnd;                             // Variable to store the window handle
    DWORD       m_dwExStyle = 0;                    // Variable to specify the extended window style
    DWORD       m_dwStyle = WS_OVERLAPPEDWINDOW;    // Variable to set the default window style
    DWORD       m_dwWindowPosX = 0;                 // Initial X coordinate of the window
    DWORD       m_dwWindowPosY = 0;                 // Initial Y coordinate of the window
    DWORD       m_dwWindowWidth;                    // Initial Width of the window
    DWORD       m_dwWindowHeight;                   // Initial Height of the window
        
public:
    // function to perform window class registration
    // hInstance : Window instance handle
    bool SetRegisterClassWindow(HINSTANCE hInstance);

    // function to create and initialize the window
    // szTitle : Window title text
    // dwWindowWidth : Initial Width of the window (default : 800)
    // dwWindowHeight : Initial Height of the window (default : 600)
    bool SetWindow(const WCHAR* szTitle, //std::wstring szTitle,
                         DWORD  dwWindowWidth = 800,
                         DWORD  dwWindowHeight = 600);

public:
    virtual ~Window() {}
};

