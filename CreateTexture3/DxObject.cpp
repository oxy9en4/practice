#include "DxObject.h"

#include "./WIC/DDSTextureLoader.h"
#include "./WIC/WICTextureLoader.h"



void Object::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pDevice = pDevice;
	m_pImmediateContext = pImmediateContext;
}


bool Object::CreateVertexBuffer()
{
	/*m_VertexList.resize(6);
	m_VertexList[0].u = 0.0f; m_VertexList[0].v = 0.0f;
	m_VertexList[1].u = 1.0f; m_VertexList[1].v = 0.0f;
	m_VertexList[2].u = 0.0f; m_VertexList[2].v = 1.0f;
	m_VertexList[3].u = 0.0f; m_VertexList[3].v = 1.0f;
	m_VertexList[4].u = 1.0f; m_VertexList[4].v = 0.0f;
	m_VertexList[5].u = 1.0f; m_VertexList[5].v = 1.0f;

	float x = randstep(-1.0f, +1.0f);
	float y = randstep(-1.0f, +1.0f);

	m_VertexList[0].x = x; m_VertexList[0].y = y; m_VertexList[0].z = 0.5f;
	m_VertexList[1].x = x + 0.3f; m_VertexList[1].y = y; m_VertexList[1].z = 0.5f;
	m_VertexList[2].x = x; m_VertexList[2].y = y - 0.3f; m_VertexList[2].z = 0.5f;
	m_VertexList[3].x = x; m_VertexList[3].y = y - 0.3f; m_VertexList[3].z = 0.5f;
	m_VertexList[4].x = x + 0.3f; m_VertexList[4].y = y; m_VertexList[4].z = 0.5f;
	m_VertexList[5].x = x + 0.3f; m_VertexList[5].y = y - 0.3f; m_VertexList[5].z = 0.5f;


	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.ByteWidth = sizeof(P_Vertex) * m_VertexList.size();
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitialData;
	ZeroMemory(&InitialData, sizeof(InitialData));
	InitialData.pSysMem = &m_VertexList.at(0);

	HRESULT hr = m_pDevice->CreateBuffer(
		&Desc,
		&InitialData,
		&m_pVertexBuffer);
	if (FAILED(hr)) return false;*/
	return true;
}

bool Object::CreateInputLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE" , 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT iNumCount = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pDevice->CreateInputLayout(
		layout,
		iNumCount,
		m_pShader->GetBufferPointer(),
		m_pShader->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr)) return false;
	return true;
}

bool Object::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(CB_Data);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = m_pDevice->CreateBuffer(
		&desc,
		nullptr,
		&m_pConstantBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


bool Object::Create(TextureMgr& texMgr, std::wstring TexFilename,
	ShaderMgr& shaderMgr, std::wstring shaderFilename)
{
	CreateVertexBuffer();
	m_pShader = shaderMgr.Load(shaderFilename);
	CreateInputLayout();
	m_pTex = texMgr.Load(TexFilename);
	return true;
}

bool Object::Init()
{
	return true;
}

bool Object::Frame()
{
	return true;
}

bool Object::Render()
{
	ID3D11ShaderResourceView* pTexSRV = nullptr;
	if (m_pTex)
	{
		m_pTex->Apply(m_pImmediateContext, 0);
	}
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

	if (m_pShader)
	{
		m_pShader->Apply(m_pImmediateContext, 0);
	}

	UINT stride = sizeof(P_Vertex);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->Draw(m_VertexList.size(), 0);
	return true;

}

bool Object::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	return true;

}
