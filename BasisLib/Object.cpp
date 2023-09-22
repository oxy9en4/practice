#include "Object.h"

void Object::SetRect(Vector2& c, float w, float h) {
	m_RT.Set(c, w, h);
}
void Object::SetRect(float x, float y, float w, float h) {
	m_RT.Set(x, y, w, h);
}

void Object::SetPos(Vector3 p) {
	m_vPos = p;
}
void Object::SetScale(Vector3 s) {
	m_vScale = s;
}

bool Object::Create(std::wstring texFilename,
					std::wstring shaderFilename) {
	CreateConstantBuffer();
	CreateVertexData(); // after Map.cpp
	CreateIndexData();	// after Map.cpp
	CreateVertexBuffer();

	m_pShader = I_Shader.Load(shaderFilename);
	CreateInputLayout();
	m_pTex = I_Tex.Load(texFilename);
	UpdateMatrix();
	return true;
}
void Object::UpdateMatrix()
{
	TBASIS_EX::TMatrix matScale, matRotate, matTranslate;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&matRotate, m_vRotation.z);
	D3DXMatrixTranslation(&matTranslate, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = matScale * matRotate * matTranslate;
}
bool Object::Init() {
	DxObject::Init();
	return true;
}
bool Object::Frame() {
	DxObject::Frame();
	return true;
}
bool Object::Render() {
	DxObject::Render();
	return true;
}
bool Object::Release() {
	DxObject::Release();
	return true;
}
void Object::SetMatrix(TBASIS_EX::TMatrix* matWorld, TBASIS_EX::TMatrix* matView, TBASIS_EX::TMatrix* matProj) {
	if (matWorld != nullptr)
		m_matWorld = *matWorld;
	if (matView != nullptr)
		m_matView = *matView;
	if (matProj != nullptr)
		m_matProj = *matProj;
	m_cbData.matWorld = m_matWorld.Transpose();
	m_cbData.matView = m_matView.Transpose();
	m_cbData.matProj = m_matProj.Transpose();
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &m_cbData, 0, 0);
}

Object::Object() {
	m_vPos = Vector3(0, 0, 0);
	m_vScale = Vector3(1, 1, 1);
	m_vRotation = Vector3(0, 0, 0);
}