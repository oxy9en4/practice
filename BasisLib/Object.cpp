#include "Object.h"

void Object::SetRect(Vector2& c, float w, float h) {
	m_RT.Set(c, w, h);
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
	CreateVertexBuffer();
	m_pShader = I_Shader.Load(shaderFilename);
	CreateInputLayout();
	m_pTex = I_Tex.Load(texFilename);
	UpdateMatrix();
	return true;
}
void Object::UpdateMatrix()
{
	Matrix matScale, matRotate, matTranslate;
	matScale.Scale(m_vScale);
	matRotate.ZRotate(m_vRotation.z);
	matTranslate.Translate(m_vPos);
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
void Object::SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj) {
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