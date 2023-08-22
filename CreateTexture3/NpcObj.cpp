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
	Matrix matScale, matRotation, matTranslate;
	matScale.Scale(m_vScale);
	matRotation.ZRotate(m_vRotation.z);
	matTranslate.Translate(m_vPos);
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
