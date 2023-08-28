#pragma once
#include "stdafx.h"
#include "Utils.h"
#include "TextureMgr.h"
#include "ShaderMgr.h"

struct CB_Data
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
};
struct PT_Vertex
{
	Vector3 p;
	Vector2 t;
};

class DxObject
{
public:
	ID3D11Device* m_pDevice = nullptr;				//积己磊
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		//府家胶 力绢
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pConstantBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	const Shader* m_pShader = nullptr;
	const Texture* m_pTex = nullptr;
	CB_Data m_cbData;
	std::vector<PT_Vertex>	m_VertexList;

public:
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool CreateVertexBuffer();
	virtual bool CreateInputLayout();
	virtual bool CreateConstantBuffer();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	virtual ~DxObject() {};
};

