#pragma once
#include "TextureMgr.h"
#include "ShaderMgr.h"

struct P_Vertex
{
	float x, y, z;
	float u, v;
};

class Object
{
	//Matrix	m_matWorld;  //青纺
	ID3D11Device*			m_pDevice = nullptr;				//积己磊
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;		//府家胶 力绢
public:
	ID3D11Buffer*			m_pVertexBuffer = nullptr;			
	ID3D11InputLayout*		m_pVertexLayout = nullptr;

	const Shader* m_pShader = nullptr;
	const Texture* m_pTex = nullptr;
	std::vector<P_Vertex>	m_VertexList;

public:
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	bool CreateVertexBuffer();
	bool CreateInputLayout();

public:
	bool Create(TextureMgr& texMgr, std::wstring TexFilename,
		ShaderMgr& shaderMgr, std::wstring shaderFilename);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};

