#pragma once
#include "std.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP = 1,
	KEY_PUSH = 2,
	KEY_HOLD = 3,
};



class Input
{
public:
	TVector3  m_vOffset = { 0,0,0 };
	POINT  m_MousePos;
	POINT  m_BeforeMousePos;
	DWORD m_dwKeyState[256];
	DWORD GetKey(DWORD key)
	{
		return m_dwKeyState[key];
	}
	static Input& GetInstance() // singleton
	{
		static Input input;
		return input;
	}
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Vector3 GetWorldPos(Vector2 vWindow, Vector3 vCamera);
	Vector2 GetWorldPosVec2(Vector2 vWindow, Vector3 vCamera);

	bool GetMouse()
	{
		return (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
	}
private:
	Input() {  };
public:
	~Input() {}
};

#define I_Input Input::GetInstance()