#pragma once
#include "std.h"

class Camera
{
public:
	Matrix m_matView;
	Matrix m_matOrthoProj;
	Vector3 m_vCameraPos;
	DWORD m_dwWindowWidth;
	DWORD m_dwWindowHeight;
public:
	bool  Init();
	bool  Frame();
	bool  Render();
	bool  Release();
public:
	bool  Create(Vector3 vPos, Vector2 size);
};

