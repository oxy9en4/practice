#include "Camera.h"
#include "Input.h"

bool Camera::Init()
{
	return true;
}

bool Camera::Frame()
{
	float fHalfWidth = m_dwWindowWidth / 2.0f;
	float fHalfHeight = m_dwWindowHeight / 2.0f;
	if (m_vCameraPos.x < -(g_fMapHalfSizeX) + fHalfWidth)
	{
		m_vCameraPos.x = -(g_fMapHalfSizeX) + fHalfWidth;
	}
	if (m_vCameraPos.y < -(g_fMapHalfSizeY) + fHalfHeight)
	{
		m_vCameraPos.y = -(g_fMapHalfSizeY) + fHalfHeight;
	}
	if (m_vCameraPos.x > (g_fMapHalfSizeX ) - fHalfWidth)
	{
		m_vCameraPos.x = (g_fMapHalfSizeX ) - fHalfWidth;
	}
	if (m_vCameraPos.y > (g_fMapHalfSizeY ) - fHalfHeight)
	{
		m_vCameraPos.y = (g_fMapHalfSizeY ) - fHalfHeight;
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

Matrix Camera::CreateLookAt(Vector3 pos, Vector3 target, Vector3 up)
{
	
	Vector3 dir = target - pos;
	dir.Normalize();
	float dot = up | dir;

	Vector3 vP = dir * dot;
	Vector3 vUp = up - vP;
	vUp.Normalize();
	Vector3 vRight = vUp ^ dir;

	Matrix tMt;
	m_matView._11 = vRight.x; m_matView._12 = vUp.x; m_matView._13 = dir.x;
	m_matView._21 = vRight.y; m_matView._22 = vUp.y; m_matView._23 = dir.y;
	m_matView._31 = vRight.z; m_matView._32 = vUp.z; m_matView._33 = dir.z;

	m_matView._41 = -(pos.x * m_matView._11 + pos.y * m_matView._21 + pos.z * m_matView._31);
	m_matView._42 = -(pos.x * m_matView._12 + pos.y * m_matView._22 + pos.z * m_matView._32);
	m_matView._43 = -(pos.x * m_matView._13 + pos.y * m_matView._23 + pos.z * m_matView._33);

	return m_matView;
}

bool Camera::Create(Vector3 pos, Vector2 size)
{
	m_vCameraPos = pos;
	m_dwWindowWidth = size.x;
	m_dwWindowHeight = size.y;
	m_matView._41 = -m_vCameraPos.x;
	m_matView._42 = -m_vCameraPos.y;
	m_matView._43 = -m_vCameraPos.z;
	m_matOrthoProj._11 = 2.0f / ((float)m_dwWindowWidth);
	m_matOrthoProj._22 = 2.0f / ((float)m_dwWindowHeight);
	return true;
}

Matrix Camera::CreatePerspectiveFov(float fFov, float fAspect, float fNear, float fFar)
{
	float h, w, q;
	h = 1 / tan(fFov * 0.5f);
	w = h / fAspect;
	q = fFar / (fFar - fNear);
	m_matPerspectiveProj._44 = 0.0f; // 원근투영 _44 원소는 0이다.
	m_matPerspectiveProj._11 = w;
	m_matPerspectiveProj._22 = h;
	m_matPerspectiveProj._33 = q;
	m_matPerspectiveProj._43 = -q * fNear;
	m_matPerspectiveProj._34 = 1;

	return m_matPerspectiveProj;
}

std::pair<float, float> Camera::ZoomInOut(float halfWidth, float halfHeight)
{
	std::pair<float, float> temp;
	temp.first = halfWidth;
	temp.second = halfHeight;

	Vector3 mouse = I_Input.GetWorldPos({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_vCameraPos);
	Vector2 mouse2 = I_Input.GetWorldPosVec2({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_vCameraPos);

	if (m_RT.ToPoint(mouse2))
		_isCamMove = false;
	else
		_isCamMove = true;

	if (_isCamMove)
	{
		Vector3 mDir = mouse - m_vCameraPos;
		mDir.Normalize();
		Vector3 velocity = mDir * 400.f * g_fSPF;
		m_vCameraPos += velocity;
	}

	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD1] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD2] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TWICE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD3] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TRIPLE;
	}

	switch (m_zoomState)
	{
	case CAMERA_ZOOM_ONCE:
	{
		m_vCameraPos.x = 0.f;
		m_vCameraPos.y = 0.f;
		m_vCameraPos.z = 0.f;

		return  temp;
	}
	case CAMERA_ZOOM_TWICE:
	{
		if (m_vCameraPos.x > g_fMapHalfSizeX - (halfWidth * 0.5f))
		{
			m_vCameraPos.x = g_fMapHalfSizeX - (halfWidth * 0.5f);
		}
		if (m_vCameraPos.x < -(g_fMapHalfSizeX)+(halfWidth * 0.5f))
		{
			m_vCameraPos.x = -(g_fMapHalfSizeX)+(halfWidth * 0.5f);
		}
		if (m_vCameraPos.y > g_fMapHalfSizeY - (halfHeight * 0.5f))
		{
			m_vCameraPos.y = g_fMapHalfSizeY - (halfHeight * 0.5f);
		}
		if (m_vCameraPos.y < -g_fMapHalfSizeY + (halfHeight * 0.5f))
		{
			m_vCameraPos.y = -g_fMapHalfSizeY + (halfHeight * 0.5f);
		}

		temp.first = halfWidth * 0.5f;
		temp.second = halfHeight * 0.5f;

		return  temp;
	}
	case CAMERA_ZOOM_TRIPLE:
	{
		if (m_vCameraPos.x > g_fMapHalfSizeX - (halfWidth * 0.33375f))
		{
			m_vCameraPos.x = g_fMapHalfSizeX - (halfWidth * 0.33375f);
		}
		if (m_vCameraPos.x < -(g_fMapHalfSizeX)+(halfWidth * 0.33375f))
		{
			m_vCameraPos.x = -(g_fMapHalfSizeX)+(halfWidth * 0.33375f);
		}
		if (m_vCameraPos.y > g_fMapHalfSizeY - (halfHeight * 0.33375f))
		{
			m_vCameraPos.y = g_fMapHalfSizeY - (halfHeight * 0.33375f);
		}
		if (m_vCameraPos.y < -(g_fMapHalfSizeY)+(halfHeight * 0.33375f))
		{
			m_vCameraPos.y = -(g_fMapHalfSizeY)+(halfHeight * 0.33375f);
		}

		temp.first = halfWidth * 0.33375f;
		temp.second = halfHeight * 0.33375f;

		return  temp;
	}
	default:
		return  temp;
	}
}
