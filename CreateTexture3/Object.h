#pragma once
#include "DxObject.h"

class Object : public DxObject
{
public:
	Vector3 m_vPos;
	Vector3 m_vScale;
	Vector3 m_vRotation;
	Matrix m_matWorld;
	Matrix m_matView;
	Matrix m_matProj;
public:
	void SetPos(Vector3 p);
	void SetScale(Vector3 s);

};