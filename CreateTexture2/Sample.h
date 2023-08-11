#pragma once
#include "Core.h"

struct P_Vertex
{
	float x, y, z;
};

class Sample : public Core
{
public:
	ID3D11Buffer*			m_pVertexBuffer = nullptr;
	ID3DBlob*				m_pVertexShaderCode;
	ID3D11InputLayout*		m_pVertexLayout = nullptr;
	ID3D11VertexShader*		m_pVS = nullptr;
	ID3D11PixelShader*		m_pPS = nullptr;
	std::vector<P_Vertex>	m_VertexList;

public:
	bool CreateVertexBuffer();
	bool LoadVertexShader();
	bool LoadPixelShader();
	bool CreateInputLayout();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};