#pragma once
#include "DxObject.h"
#include "DirectXTex.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"

class Object : public DxObject
{
public:
	bool			m_bDead = false;
public:
	Vector3			m_vPos;
	Vector3			m_vScale;
	Vector3			m_vRotation;
	Matrix			m_matWorld;
	Matrix			m_matView;
	Matrix			m_matProj;
	Rect			m_RT;
	virtual void SetRect(Vector2& c, float w, float h);
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
	virtual void SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj);
	virtual void Move(float fSecond) {};
public:
	Object();
	virtual ~Object() {}
};