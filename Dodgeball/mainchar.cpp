#include "mainchar.h"

bool mainchar::Init()
{
	Bullet = std::make_unique<bullet>();
	return true;
}


void mainchar::SetUVFrame(int iNumRow, int iNumColumn)
{
	UVRect tRt;
	Vector2 uv;

	// 16x9
	float fOffsetX = 1.0f / iNumColumn;
	float fOffsetY = 1.0f / iNumRow;
	if (iNumRow == 9)
	{
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
					if (column < 4)
						m_AttackList.push_back(tRt);
				}
				if (row == 8)
				{
					if (column < 1)
						m_IdleList.push_back(tRt);
				}
				if (row == 7)
				{
					if (column < 10 && column > 1)
						m_DodgeList.push_back(tRt);
				}
			}
		}
		m_fOffsetTime = m_fAnimTimer / m_pUVList.size();
	}
	if (iNumRow == 7)
	{
		int row = 4;
		uv.y = fOffsetY * row;
		for (int column = 2; column < iNumColumn; column++)
		{
			uv.x = fOffsetX * column;
			tRt.m_Min = uv;
			tRt.m_Max.x = uv.x + fOffsetX;
			tRt.m_Max.y = uv.y + fOffsetY;
			m_pUVList.push_back(tRt);
			m_DeathList.push_back(tRt);

		}
		m_fOffsetTime = m_fAnimTimer / m_pUVList.size();
	}
}


bool mainchar::Frame()
{
	// ���� ��ġ�� ��ǥ ��ġ�� �̵��ϴ� �ڵ带 �߰��մϴ�.
	float moveSpeed = 150.0f; // �ʴ� �̵� �ӵ� (�ȼ�/��)
	float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;
	if (m_State == CHAR_DODGE) maxMoveDistanceThisFrame *= 1.5;
	if ((mTarget - m_vPos).Length() > 1.0f)
	{
		// ��ǥ ��ġ���� �ִ� �̵� �Ÿ���ŭ �̵��մϴ�.
		Vector3 moveDirection = (mTarget - m_vPos).NormVector();
		m_vPos += moveDirection * maxMoveDistanceThisFrame;
	}
	else
	{
		// ��ǥ ��ġ�� ������ ���, ��ġ�� ��ǥ ��ġ�� �����մϴ�.
		m_vPos = mTarget;
	}
	
	PlaneObj::Frame();
	m_fElapsedTimer += g_fSPF;
	if (m_fElapsedTimer >= m_fOffsetTime && m_State < CHAR_CANCLE) // cancle ���°� �ƴ϶�� index ����
	{
		m_iCurrentAnimIndex++;
		m_fElapsedTimer -= m_fOffsetTime;
	}
	else if (m_fElapsedTimer >= m_fOffsetTime && m_State == CHAR_CANCLE) // cancle ���¶�� �����
	{
		m_iCurrentAnimIndex--;
		m_fElapsedTimer -= m_fOffsetTime;
	}
	if (Bullet->visible) Bullet->Frame();
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
			m_iCurrentAnimIndex = m_AttackList.size() - 1;
			m_State = CHAR_CANCLE;

			Bullet->m_iCurrentAnimIndex = 0;
			Bullet->visible = true;
		}
		uv = m_AttackList[m_iCurrentAnimIndex];
		break;
	case CHAR_DODGE:
		if (m_iCurrentAnimIndex >= m_DodgeList.size())
		{
			m_iCurrentAnimIndex = 0;
			m_State = CHAR_IDLE;
		}
		uv = m_DodgeList[m_iCurrentAnimIndex];
		break;
	case CHAR_CANCLE:
		if (m_iCurrentAnimIndex == 0)
		{
			m_State = CHAR_IDLE;
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

	Bullet->Render();
	return true;
}