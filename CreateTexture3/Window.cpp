#include "stdafx.h"
#include "Window.h"
HWND g_hWnd;

// Window Procedure : Handles window messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY: // When the window is destroyed, post a quit message and exit
        PostQuitMessage(0);
        break;
    default:        // For unhandled messages, pass them to the default window procedure
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// function to register the window class
bool Window::SetRegisterClassWindow(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;               // Redraw window when resized horizonally or vertically
    wcex.lpfnWndProc = WndProc;                         // Set the window procedure to handle window events
    wcex.hInstance = hInstance;
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)); // Set the background color
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);      // Set the Cursor shape
    wcex.lpszClassName = L"KGCA Window";                // Set the window class name
    WORD ret = RegisterClassExW(&wcex);                 // Register the window class
	return true;
}


//function to create the window
bool Window::SetWindow(const WCHAR* szTitle, // std::wstring szTitle,
                            DWORD dwWindowWidth,
                            DWORD dwWindowHeight)
{
    m_dwWindowWidth = dwWindowWidth;
    m_dwWindowHeight = dwWindowHeight;
#ifndef _DEBUG
    // In debug mode, keep the window always on top and set it as a popup window
    m_dwExStyle = WS_EX_TOPMOST;
    m_dwStyle = WS_POPUPWINDOW;
#else
    DWORD dwExStyle = WS_EX_APPWINDOW;
#endif

    // Create the window
    m_hWnd = CreateWindowEx(m_dwExStyle, L"KGCA Window", szTitle,
                            //szTitle.c_str(),
                            m_dwStyle,
                            m_dwWindowPosX, m_dwWindowPosY,
                            m_dwWindowWidth, m_dwWindowHeight,
                            nullptr, nullptr, m_hInstance, nullptr);
    // If window creation fails, return FALSE
    if (!m_hWnd)
    {
        return FALSE;
    }

    // Show the window
    g_hWnd = m_hWnd;
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
	return true;
}
