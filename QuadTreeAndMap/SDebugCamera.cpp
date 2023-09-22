#include "SDebugCamera.h"
#include "Input.h"

bool SDebugCamera::Init()
{
	TCamera::Init();
    return true;
}

//what Frame have to do?
bool SDebugCamera::Frame()
{
	if (I_Input.m_dwKeyState[VK_SPACE] == KEY_HOLD)
	{
		m_fSpeed += g_fSPF * m_fSpeed;
	}
	m_fSpeed -= g_fSPF * m_fSpeed * 0.5f;
	m_fSpeed = max(10.0f, m_fSpeed);

	if (I_Input.m_dwKeyState['W'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vLook * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos + vOffset;
	}
	if (I_Input.m_dwKeyState['S'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vLook * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos - vOffset;
	}
	if (I_Input.m_dwKeyState['A'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vSide * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos + vOffset;
	}
	if (I_Input.m_dwKeyState['D'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vSide * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos - vOffset;
	}
	if (I_Input.m_dwKeyState['Q'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vUp * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos + vOffset;
	}
	if (I_Input.m_dwKeyState['E'] == KEY_HOLD)
	{
		TVector3 vOffset = m_vUp * g_fSPF * m_fSpeed;
		m_vCameraPos = m_vCameraPos - vOffset;
	}
	if (I_Input.m_dwKeyState[VK_LBUTTON] == KEY_HOLD)
	{
		float x = Input::GetInstance().m_vOffset.x;
		float y = Input::GetInstance().m_vOffset.y;
		m_fCameraYaw += XMConvertToRadians(x * 0.1f);
		m_fCameraPitch += XMConvertToRadians(y * 0.1f);
	}

	TQuaternion gRotation;
	TMatrix matRotation;
	D3DXQuaternionRotationYawPitchRoll(&gRotation, m_fCameraYaw, m_fCameraPitch, 0);
	D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL, &gRotation, &m_vCameraPos);
	D3DXMatrixInverse(&m_matView, NULL, &matRotation);
	UpdateVector();
	//CreateLookAt(m_vCameraPos, m_vTargetPos);
	return true;

    return true;
}

bool SDebugCamera::Render()
{
	TCamera::Render();
    return true;
}

bool SDebugCamera::Release()
{
	TCamera::Release();
    return true;
}
