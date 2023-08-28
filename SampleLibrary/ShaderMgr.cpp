#include "ShaderMgr.h"


bool Shader::LoadVertexShader(ID3D11Device* pDevice, std::wstring filename)
{
	ID3DBlob* ErrorCode;
	HRESULT hr = D3DCompileFromFile(
		L"Plane.hlsl",
		nullptr,
		nullptr,
		"VS",
		"vs_5_0",
		0,
		0,
		&m_pVertexShaderCode,
		&ErrorCode);
	if (FAILED(hr))
	{
		TCHAR pMessage[500];
		mbstowcs(pMessage, (CHAR*)ErrorCode->GetBufferPointer(), 500);
		MessageBox(NULL, pMessage, L"ERROR", MB_OK);
		return false;
		// Code for Error Situation	}
	}
	if (ErrorCode) ErrorCode->Release();

	hr = pDevice->CreateVertexShader(
		m_pVertexShaderCode->GetBufferPointer(),
		m_pVertexShaderCode->GetBufferSize(),
		nullptr,
		&m_pVS);

	if (FAILED(hr)) return false;
	return true;
}

bool Shader::LoadPixelShader(ID3D11Device* pDevice, std::wstring filename)
{

	ID3DBlob* ShaderCode;
	ID3DBlob* ErrorCode;

	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr,
		nullptr,
		"PS",
		"ps_5_0",
		0,
		0,
		&ShaderCode,
		&ErrorCode);
	if (FAILED(hr))
	{
		TCHAR pMessage[500];
		mbstowcs(pMessage, (CHAR*)ErrorCode->GetBufferPointer(), 500);
		MessageBox(NULL, pMessage, L"ERROR", MB_OK);
		return false;
		// Code for Error Situation	}
	}
	if (ErrorCode) ErrorCode->Release();

	hr = pDevice->CreatePixelShader(
		ShaderCode->GetBufferPointer(),
		ShaderCode->GetBufferSize(),
		nullptr,
		&m_pPS);
	if (ShaderCode) ShaderCode->Release();

	if (FAILED(hr)) return false;
	return true;
}

bool Shader::Load(ID3D11Device* pDevice, std::wstring filename)
{
	if (LoadVertexShader(pDevice, filename) == false) return false;
	if (LoadPixelShader(pDevice, filename) == false) return false;
	return true;
}

bool Shader::Release()
{
	if (m_pVertexShaderCode) m_pVertexShaderCode->Release();
	if (m_pVS) m_pVS->Release();
	if (m_pPS) m_pPS->Release();
	if (m_pDS) m_pDS->Release();
	if (m_pHS) m_pHS->Release();
	if (m_pGS) m_pGS->Release();
	if (m_pCS) m_pCS->Release();
	m_pVertexShaderCode = nullptr;

	m_pVS = nullptr;
	m_pDS = nullptr;
	m_pHS = nullptr;
	m_pGS = nullptr;
	m_pPS = nullptr;
	m_pCS = nullptr;
	return true;
}



void ShaderMgr::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pDevice = pDevice;
	m_pImmediateContext = pImmediateContext;
}


// 폴더의 최종경로의 위치를 검색.( 마지막 "/"의 위치 탐색 )
// 
const Shader* ShaderMgr::Load(std::wstring szShaderFilepath)
{
	std::size_t found = szShaderFilepath.find_last_of(L"/");
	std::wstring path = szShaderFilepath.substr(0, found + 1);
	std::wstring key = szShaderFilepath.substr(found + 1);
	const Shader* data = GetPtr(key);
	if (data != nullptr) return data;
	Shader* newData = new Shader;
	if (newData->Load(m_pDevice, szShaderFilepath))
	{
		m_list.insert(std::make_pair(key, newData));
		return newData;
	}
	delete newData;
	return nullptr;


	return nullptr;
}

const Shader* ShaderMgr::GetPtr(std::wstring key)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter) return nullptr;
	return iter->second;
}

bool ShaderMgr::Get(std::wstring key, Shader& ret)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter) return false;
	ret = *(iter->second);
	return true;
}

bool ShaderMgr::Release()
{
	for (auto& data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
	return true;
}



ShaderMgr::ShaderMgr()
{
}

ShaderMgr::~ShaderMgr()
{
	for (auto& data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
}
