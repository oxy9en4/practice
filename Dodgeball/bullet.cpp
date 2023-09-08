#include "bullet.h"



void bullet::SetUVFrame(int iNumRow, int iNumColumn)
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
			if (row == 2)
			{
				m_UVList.push_back(tRt);
			}
		}
	}
	m_fOffsetTime = m_fAnimTimer / m_UVList.size() * 0.08f;
}


bool bullet::Frame()
{

	// 현재 위치를 목표 위치로 이동하는 코드를 추가합니다.
	float moveSpeed = 400.0f; // 초당 이동 속도 (픽셀/초)
	float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;


	Vector3 moveDirection = mDir.NormVector();
	m_vPos += moveDirection * maxMoveDistanceThisFrame;

	PlaneObj::Frame();
	m_fElapsedTimer += g_fSPF;
	if (m_fElapsedTimer >= m_fOffsetTime)
	{
		if (m_iCurrentAnimIndex < m_UVList.size() - 1) m_iCurrentAnimIndex++;
		m_fElapsedTimer -= m_fOffsetTime;
	}
	lifeTime += g_fSPF;
	if (lifeTime > 2.0f)
	{
		lifeTime = 0.0f;
		visible = false;
		m_iCurrentAnimIndex = 0;
		Vector2 tmp = {3000, 3000};
		SetRect(tmp, m_RT.m_fWidth, m_RT.m_fHeight);
	}

	return true;
}
bool bullet::Render()
{
	if (!visible) return false;
	UVRect uv = m_UVList[m_iCurrentAnimIndex];

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