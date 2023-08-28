#pragma once
#include "std.h"

class Shader
{
	ID3D11VertexShader*		m_pVS = nullptr;
	ID3D11PixelShader*		m_pPS = nullptr;

	ID3D11HullShader*		 m_pHS = nullptr;
	ID3D11DomainShader*		 m_pDS = nullptr;
	ID3D11ComputeShader*	 m_pCS = nullptr;
	ID3D11GeometryShader*	 m_pGS = nullptr;
	ID3DBlob*				m_pVertexShaderCode;			// 소스코드

public:
	
	std::wstring m_csName;		//파일 이름
	std::wstring m_csPath;		//파일 경로
	LPVOID GetBufferPointer(void) const {
		return m_pVertexShaderCode->GetBufferPointer();
	}
	SIZE_T GetBufferSize(void) const {
		return m_pVertexShaderCode->GetBufferSize();
	}
	void Apply(ID3D11DeviceContext* pContext, int iSlot) const
	{
		pContext->VSSetShader(m_pVS, NULL, 0);
		pContext->PSSetShader(m_pPS, NULL, 0);

		pContext->HSSetShader(m_pHS, NULL, 0);
		pContext->DSSetShader(m_pDS, NULL, 0);
		pContext->CSSetShader(m_pCS, NULL, 0);
		pContext->GSSetShader(m_pGS, NULL, 0);
	}
	bool LoadVertexShader(ID3D11Device* pDevice, std::wstring filename);
	bool LoadPixelShader(ID3D11Device* pDevice, std::wstring filename);
	bool Load(ID3D11Device* pDevice, std::wstring filename);
	bool Release();

};

class ShaderMgr
{
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	using MyList = std::map<std::wstring, Shader*>;
public:
	static ShaderMgr& GetInstance() {
		static ShaderMgr input;
		return input;
	}
public:
	MyList m_list;
public:
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);

	const Shader* Load(std::wstring szFilepath);
	const Shader* GetPtr(std::wstring key);
	bool Get(std::wstring key, Shader& ret);
	bool Release();
private:
	ShaderMgr();
public:
	virtual ~ShaderMgr();
};

#define I_Shader ShaderMgr::GetInstance()