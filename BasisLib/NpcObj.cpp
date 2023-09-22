#include "NpcObj.h"

void NpcObj::Move(float fSecond)
{
	Vector3 vVelocity = m_vDirection * 500.0f * fSecond;
	m_vPos = m_vPos + vVelocity;

	if (m_vPos.x < -1000.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = -1000.0f;
	}
	if (m_vPos.y < -1000.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = -1000.0f;
	}
	if (m_vPos.x > 1000.0f)
	{
		m_vDirection.x *= -1.0f;
		m_vPos.x = 1000.0f;
	}
	if (m_vPos.y > 1000.0f)
	{
		m_vDirection.y *= -1.0f;
		m_vPos.y = 1000.0f;
	}
	Vector2 rt = { m_vPos.x, m_vPos.y }; // 충돌 처리를 위해 위치 데이터 업데이트
	SetRect(rt,		m_vScale.x * 2.0f, m_vScale.y * 2.0f);
}

bool NpcObj::Frame()
{
	TBASIS_EX::TMatrix matScale, matRotation, matTranslate;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&matRotation, m_vRotation.z);
	D3DXMatrixTranslation(&matTranslate, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = matScale * matRotation * matTranslate;
	return true;
}

NpcObj::NpcObj()
{
	m_vDirection = { randstep(-1,1), randstep(-1,1),0 };
}

NpcObj::~NpcObj()
{
}
