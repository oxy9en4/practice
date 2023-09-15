#pragma once
#include "std.h"


enum E_CameraZoomState
{
	CAMERA_ZOOM_ONCE,
	CAMERA_ZOOM_TWICE,
	CAMERA_ZOOM_TRIPLE,
	CAMERA_ZOOM_NONE
};


class Camera
{
public:
	Matrix		m_matView;
	Matrix		m_matViewInverse;

	Matrix		m_matOrthoProj;
	Matrix		m_matOrthoProjInverse;
	Matrix		m_matPerspectiveProj;

	Vector3		m_vCameraPos;
	Vector3		m_vTargetPos;
	DWORD		m_dwWindowWidth;
	DWORD		m_dwWindowHeight;

	E_CameraZoomState       m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
	Rect		m_RT;

	std::pair<float, float> ProjectPair;

	float m_Near;
	float m_Far;
	float m_CameraMoveSpeed = 400.0f;
	bool _isCamMove = false;
public:
	bool  Init();
	bool  Frame();
	bool  Render();
	bool  Release();
public:

	Matrix CreateLookAt(Vector3 pos, Vector3 target, Vector3 up = { 0,1,0 } );
	Matrix CreatePerspectiveFov(float fFov, float fAspect, float fNear, float fFar);
	bool Create(Vector3 pos, Vector2 size);

	std::pair<float, float> ZoomInOut(float halfWidth, float halfHeight);
};

