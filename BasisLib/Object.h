#pragma once
#include "DxObject.h"
#include "DirectXTex.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "TMath.h"

class Object : public DxObject
{
public:
	bool			m_bDead = false;
	int             m_iCollisionID = -1;
	int             m_iSelectID = -1;
	virtual void    MouseOverlap(Vector2 pt, DWORD state)
	{
		int k = 0;
	}
public:
	Vector3			m_vPos;
	Vector3			m_vScale;
	Vector3			m_vRotation;
	TBASIS_EX::TMatrix         m_matWorld;
	TBASIS_EX::TMatrix         m_matView;
	TBASIS_EX::TMatrix         m_matProj;
	TRect			m_RT;
	W_STR           m_szName;
	void            SetName(W_STR name) { m_szName = name; }
	virtual void SetRect(Vector2& c, float w, float h);
	virtual void SetRect(float x, float y, float w, float h);
public:
	void SetPos(Vector3 p);
	void SetScale(Vector3 s);
public:
	virtual bool Create(std::wstring shaderFilename,
						std::wstring texFilename);
	virtual void UpdateMatrix();
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void SetMatrix(TBASIS_EX::TMatrix* matWorld, TBASIS_EX::TMatrix* matView, TBASIS_EX::TMatrix* matProj);
	virtual void Move(float fSecond) {};
public:
	Object();
	virtual ~Object() {}
};