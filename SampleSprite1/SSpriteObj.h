#pragma once
#include "PlaneObj.h"

struct SSpriteInfo
{
	Vector3 pos;
	Vector3 size;
	W_STR texFilename;
	W_STR texAlphaFilename;
};

class SSpriteObj : public PlaneObj
{
public:
	const std::unique_ptr<Texture> m_AlphaTex;
	float m_fOffsetTime = 0.f;
	float m_fAnimTime = 0.f;
	int m_iCurrentAnimIndex = 0;
public:
	virtual bool Load(
		ID3D11Device* pDevice,
		ID3D11DeviceContext* pImmediateContext,
		SSpriteInfo);
};

