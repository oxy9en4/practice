#include "Camera.h"


bool Camera::Init()
{
	return true;
}

bool Camera::Frame()
{
	float fHalfWidth = m_dwWindowWidth / 2.0f;
	float fHalfHeight = m_dwWindowHeight / 2.0f;
	if (m_vCameraPos.x < -(g_fMapSizeX / 2.0f) + fHalfWidth)
	{
		m_vCameraPos.x = -(g_fMapSizeX / 2.0f) + fHalfWidth;
	}
	if (m_vCameraPos.y < -(g_fMapSizeY / 2.0f) + fHalfHeight)
	{
		m_vCameraPos.y = -(g_fMapSizeY / 2.0f) + fHalfHeight;
	}
	if (m_vCameraPos.x > (g_fMapSizeX / 2.0f) - fHalfWidth)
	{
		m_vCameraPos.x = (g_fMapSizeX / 2.0f) - fHalfWidth;
	}
	if (m_vCameraPos.y > (g_fMapSizeY / 2.0f) - fHalfHeight)
	{
		m_vCameraPos.y = (g_fMapSizeY / 2.0f) - fHalfHeight;
	}
	m_matView._41 = -m_vCameraPos.x;
	m_matView._42 = -m_vCameraPos.y;
	m_matView._43 = -m_vCameraPos.z;
	m_matOrthoProj._11 = 2.0f / ((float)m_dwWindowWidth);
	m_matOrthoProj._22 = 2.0f / ((float)m_dwWindowHeight);
	return true;
}

bool Camera::Render()
{
	return true;
}

bool Camera::Release()
{
	return true;
}

bool Camera::Create(Vector3 vPos, Vector2 size)
{
	m_vCameraPos = vPos;
	m_dwWindowWidth = size.x;
	m_dwWindowHeight = size.y;
	return true;
}
