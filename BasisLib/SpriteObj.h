#pragma once
#include "PlaneObj.h"
struct SpriteInfo
{
	int			iNumRow;
	int			iNumColumn;
	Vector3	p;
	Vector3	s;
	float		fAnimTimer;
	float		fElapsedTimer; // 에니메이션 가동 시간
	W_STR		texFile;
	W_STR		texAlphaFile;
	W_STR		shaderFile;
	T_STR_VECTOR texList;
	void Reset()
	{
		iNumRow = 1;
		iNumColumn = 1;
		fAnimTimer = 1.0f;
		fElapsedTimer = 0.0f;
		p = { 1.0f, 1.0f, 1.0f };
		s = { 0.0f, 0.0f, 0.0f };
		texList.clear();
		texFile = L"";
		texAlphaFile = L"";
		shaderFile = L"";
	}
	SpriteInfo()
	{
		Reset();
	}
};

class SpriteObj : public PlaneObj
{
public:
	const	Texture* m_pAlphaTex = nullptr;
	float	m_fAnimTimer = 1.0f;  // 전체 시간
	float	m_fOffsetTime = 0.0f;	// 1프레임 교체시간
	float	m_fElapsedTimer = 0.0f; // 누적시간
	int		m_iCurrentAnimIndex = 0;
	int		m_iNumSpriteX = 1;
	int		m_iNumSpriteY = 1;
	SpriteInfo m_InitSpriteInfo;
public:
	virtual bool   Render() override;
	virtual int    GetMaxSize() { return 1; }
	virtual bool  Load(
		ID3D11Device* pDevice,
		ID3D11DeviceContext* pImmediateContext,
		SpriteInfo);
	virtual bool  LoadTexArray(T_STR_VECTOR& texList) { return true; };
	virtual void  SetUVFrame(int iNumRow, int iNumColumn) {}

};
// 텍스쳐 교체 에니메이션
class SpriteTexture : public SpriteObj
{
public:
	std::vector<const Texture*>  m_pTexList;
public:
	virtual int    GetMaxSize() { return m_pTexList.size(); }
	virtual bool   LoadTexArray(T_STR_VECTOR& texList) override;
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	SpriteTexture();
	virtual ~SpriteTexture();
};
// UV 교체 에니메이션
class SpriteUV : public SpriteObj
{
public:
	std::vector<UVRect>  m_pUVList;
	void  SetUVFrame(int iNumRow, int iNumColumn) override;
	void  SetNumSprite(int x, int y)
	{
		m_iNumSpriteX = 1;
		m_iNumSpriteY = 1;
	}
public:
	virtual int    GetMaxSize() { return m_pUVList.size(); }
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	SpriteUV();
	virtual ~SpriteUV();
};

