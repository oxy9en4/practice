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

	m_vOffset.x = m_MousePos.x - m_BeforeMousePos.x;
	m_vOffset.y = m_MousePos.y - m_BeforeMousePos.y;

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

	m_BeforeMousePos = m_MousePos;
	return true;
}

bool Input::Render()
{

	return true;
}

bool Input::Release()
{
	return true;
}


Vector3 Input::GetWorldPos(Vector2 vWindow, Vector3 vCamera)
{
	float fHalfWidth = vWindow.x / 2.0f;
	float fHalfHeight = vWindow.y / 2.0f;

	// client
	Vector3 vMouse = { (float)m_MousePos.x, (float)m_MousePos.y , 0.0f };
	// world
	Vector2 vMouseWorldLT = { vCamera.x - fHalfWidth,
							   vCamera.y + fHalfHeight };
	vMouse.x = vMouseWorldLT.x + vMouse.x;
	vMouse.y = vMouseWorldLT.y - vMouse.y;
	return vMouse;
}

Vector2 Input::GetWorldPosVec2(Vector2 vWindow, Vector3 vCamera)
{
	float fHalfWidth = vWindow.x / 2.0f;
	float fHalfHeight = vWindow.y / 2.0f;

	// client
	Vector2 vMouse = { (float)m_MousePos.x, (float)m_MousePos.y };
	// world
	Vector2 vMouseWorldLT = { vCamera.x - fHalfWidth,
							   vCamera.y + fHalfHeight };
	vMouse.x = vMouseWorldLT.x + (vMouse.x);
	vMouse.y = vMouseWorldLT.y - (vMouse.y);
	return vMouse;
}

