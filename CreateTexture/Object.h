#pragma once

struct P_Vertex
{
	float x, y, z;
	float u, v;
};

class Object
{
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
public:
	ID3D11Buffer*			m_pVertexBuffer = nullptr;
	ID3DBlob*				m_pVertexShaderCode;
	ID3D11InputLayout*		m_pVertexLayout = nullptr;
	ID3D11VertexShader*		m_pVS = nullptr;
	ID3D11PixelShader*		m_pPS = nullptr;
	ID3D11ShaderResourceView* m_pTexSRV = nullptr;

	std::vector<P_Vertex>	m_VertexList;

public:
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	bool CreateVertexBuffer();
	bool LoadVertexShader();
	bool LoadPixelShader();
	bool CreateInputLayout();
	bool LoadTextureFile(std::wstring filename);

public:
	bool Create(std::wstring texFilename);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};
