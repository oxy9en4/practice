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
	POINT m_MousePos;
	DWORD m_dwKeyState[256];
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