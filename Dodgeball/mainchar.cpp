#include "mainchar.h"


void mainchar::SetUVFrame(int iNumRow, int iNumColumn)
{
	UVRect tRt;
	Vector2 uv;

	// 16x9
	float fOffsetX = 1.0f / iNumColumn;
	float fOffsetY = 1.0f / iNumRow;
	for (int row = 0; row < iNumRow; row++)
	{
		uv.y = fOffsetY * row;
		for (int column = 0; column < iNumColumn; column++)
		{
			uv.x = fOffsetX * column;
			tRt.m_Min = uv;
			tRt.m_Max.x = uv.x + fOffsetX;
			tRt.m_Max.y = uv.y + fOffsetY;
			m_pUVList.push_back(tRt);
			if (row == 0)
			{
				if(column < 4)
					m_AttackList.push_back(tRt);
			}
			if (row == 8)
			{
				if (column < 1)
					m_IdleList.push_back(tRt);
			}
			if (row == 7)
			{
				if (column < 7 && column > 1)
					m_DodgeList.push_back(tRt);
			}
		}
	}
	m_fOffsetTime = m_fAnimTimer / m_pUVList.size();
}


bool mainchar::Frame()
{
	// 현재 위치를 목표 위치로 이동하는 코드를 추가합니다.
	float moveSpeed = 150.0f; // 초당 이동 속도 (픽셀/초)
	float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;
	if (m_State == 2) maxMoveDistanceThisFrame *= 1.5;
	if ((mTarget - m_vPos).Length() > 1.0f)
	{
		// 목표 위치까지 최대 이동 거리만큼 이동합니다.
		Vector3 moveDirection = mDir.NormVector();
		m_vPos += moveDirection * maxMoveDistanceThisFrame;
	}
	else
	{
		// 목표 위치에 도착한 경우, 위치를 목표 위치로 설정합니다.
		m_vPos = mTarget;
	}
	
	PlaneObj::Frame();
	m_fElapsedTimer += g_fSPF;
	if (m_fElapsedTimer >= m_fOffsetTime && m_State < 3)
	{
		m_iCurrentAnimIndex++;
		m_fElapsedTimer -= m_fOffsetTime;
	}
	else if (m_fElapsedTimer >= m_fOffsetTime && m_State == 3)
	{
		m_iCurrentAnimIndex--;
		m_fElapsedTimer -= m_fOffsetTime;
	}
	
	return true;
}
bool mainchar::Render()
{
	UVRect uv;
	switch (m_State)
	{
	case CHAR_IDLE:
		if (m_iCurrentAnimIndex >= m_IdleList.size())
		{
			m_iCurrentAnimIndex = 0;
		}
		uv = m_IdleList[m_iCurrentAnimIndex];
		break;
	case CHAR_ATTACK:
		if (m_iCurrentAnimIndex >= m_AttackList.size())
		{
			m_iCurrentAnimIndex = 0;
			m_State = 0;
		}
		uv = m_AttackList[m_iCurrentAnimIndex];
		break;
	case CHAR_DODGE:
		if (m_iCurrentAnimIndex >= m_DodgeList.size())
		{
			m_iCurrentAnimIndex = 0;
			m_State = 0;
		}
		uv = m_DodgeList[m_iCurrentAnimIndex];
		break;
	case CHAR_CANCLE:
		if (m_iCurrentAnimIndex == 0)
		{
			m_State = 0;
		}
		uv = m_AttackList[m_iCurrentAnimIndex];
		break;
	}
	m_VertexList[0].t = uv.m_Min;
	m_VertexList[1].t.x = uv.m_Max.x;
	m_VertexList[1].t.y = uv.m_Min.y;

	m_VertexList[2].t.x = uv.m_Min.x;
	m_VertexList[2].t.y = uv.m_Max.y;
	m_VertexList[3].t = m_VertexList[2].t;

	m_VertexList[4].t = m_VertexList[1].t;
	m_VertexList[5].t = uv.m_Max;

	m_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);

	PreRender();
	PostRender();
	return true;
}