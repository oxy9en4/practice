#pragma once
#include "TCamera.h"

class SDebugCamera : public TCamera
{
public:
	float m_fCameraYaw = 0.f;
	float m_fCameraPitch = 45.f;
	float m_fCameraRoll = 0.f;
public:
	virtual bool Init() ;
	virtual bool Frame() ;
	virtual bool Render() ;
	virtual bool Release() ;
};