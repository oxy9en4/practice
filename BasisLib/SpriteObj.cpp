#include "SpriteObj.h"
bool  SpriteObj::Load(
	ID3D11Device* pDevice,
	ID3D11DeviceContext* pContext,
	SpriteInfo info)
{
	m_InitSpriteInfo = info;
	m_fAnimTimer = info.fAnimTimer;
	m_iNumSpriteX = info.iNumRow;
	m_iNumSpriteY = info.iNumColumn;
	Set(pDevice, pContext);
	SetPos(info.p);
	SetScale(info.s);
	if (!info.texAlphaFile.empty())
	{
		this->m_pAlphaTex = I_Tex.Load(info.texAlphaFile);
	}
	LoadTexArray(info.texList);
	SetUVFrame(info.iNumRow, info.iNumColumn);
	return Create(info.texFile, info.shaderFile);
}
void SpriteObj::UpdateDir(Vector3 m_TargetPosition)
{
	// 현재 위치와 목표 위치 간의 거리를 계산합니다.
	
	mDir = m_TargetPosition - m_vPos;
	// 회전 각도를 계산합니다.
	Vector3 forwardVector = Vector3(1.0f, 0.0f, 0.0f); // 현재 앞 방향
	float angle = forwardVector.Angle(mDir);
	angle = DegreeToRadian(angle);
	m_vRotation.z = angle;

		
}
bool SpriteObj::Render()
{
	PreRender();
	if (m_pAlphaTex)
	{
		m_pAlphaTex->Apply(m_pImmediateContext, 1);
	}
	PostRender();
	return true;
}
bool   SpriteTexture::LoadTexArray(T_STR_VECTOR& texList)
{
	for (auto& texname : texList)
	{
		const Texture* pTex = I_Tex.Load(texname);
		m_pTexList.push_back(pTex);
	}
	m_fOffsetTime = m_fAnimTimer / m_pTexList.size();
	return true;
}
bool SpriteTexture::Init()
{
	PlaneObj::Init();
	return true;
}
bool SpriteTexture::Frame()
{

	PlaneObj::Frame();
	m_fElapsedTimer += g_fSPF;
	if (m_pTexList[m_iCurrentAnimIndex] != nullptr)
	{
		if (m_fElapsedTimer >= m_fOffsetTime)
		{
			m_iCurrentAnimIndex++;
			if (m_iCurrentAnimIndex >= m_pTexList.size())
			{
				m_iCurrentAnimIndex = 0;
			}
			m_fElapsedTimer -= m_fOffsetTime;
		}
	}

	return true;
}
bool SpriteTexture::Render()
{
	PreRender();
	m_pTexList[m_iCurrentAnimIndex]->Apply(m_pImmediateContext, 0);
	PostRender();
	return true;
}
bool SpriteTexture::Release()
{
	PlaneObj::Release();
	return true;
}

SpriteTexture::SpriteTexture()
{
	Init();
}
SpriteTexture::~SpriteTexture()
{
	Release();
}

void SpriteUV::SetUVFrame(int iNumRow, int iNumColumn)
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
		}
	}
	m_fOffsetTime = m_fAnimTimer / m_pUVList.size();
}
bool SpriteUV::Init()
{
	PlaneObj::Init();
	return true;
}
bool SpriteUV::Frame()
{
	// 현재 위치를 목표 위치로 이동하는 코드를 추가합니다.
	float moveSpeed = 200.0f; // 초당 이동 속도 (픽셀/초)
	float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;

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
	if (m_fElapsedTimer >= m_fOffsetTime)
	{
		m_iCurrentAnimIndex++;
		if (m_iCurrentAnimIndex >= m_pUVList.size())
		{
			m_iCurrentAnimIndex = 0;
		}
		m_fElapsedTimer -= m_fOffsetTime;
	}
	return true;
}
bool SpriteUV::Render()
{
	UVRect uv = m_pUVList[m_iCurrentAnimIndex];
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
bool SpriteUV::Release()
{
	PlaneObj::Release();
	return true;
}

SpriteUV::SpriteUV()
{
	Init();
}
SpriteUV::~SpriteUV()
{
	Release();
}