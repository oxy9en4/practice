#include "Input.h"

bool Input::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(m_dwKeyState));
	return true;
}

bool Input::Frame()
{
	::GetCursorPos(&m_MousePos); // screen position
	::ScreenToClient(g_hWnd, &m_MousePos);

	for (int ikey = 0; ikey < 256; ++ikey) {
		SHORT s = GetAsyncKeyState(ikey);
		if (s & 0x8000) // 1000 0000 0000 0000
		{
			if (m_dwKeyState[ikey] == KEY_FREE) // FREE였다면 PUSH, 아니라면 HOLD
				m_dwKeyState[ikey] = KEY_PUSH;
			else
				m_dwKeyState[ikey] = KEY_HOLD;
		}
		else
			if (m_dwKeyState[ikey] == KEY_PUSH || // PUSH거나 HOLD였다면 UP, 아니라면 FREE
				m_dwKeyState[ikey] == KEY_HOLD)
				m_dwKeyState[ikey] = KEY_UP;
			else
				m_dwKeyState[ikey] = KEY_FREE;
	}
	return true;
}

bool Input::Render()
{
#ifdef _DEBUG
	std::wstring mousPos = std::to_wstring(m_MousePos.x);
	mousPos += L", ";
	mousPos += std::to_wstring(m_MousePos.y);
	mousPos += L"\n";
	DebugString(mousPos.c_str());
#endif
	return true;
}

bool Input::Release()
{
	return true;
}
