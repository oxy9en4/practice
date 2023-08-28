#pragma once
#include "std.h"

class Texture
{
	ID3D11ShaderResourceView* m_pTexSRV = nullptr;
public:
	std::wstring m_wsName;
	std::wstring m_wsPath;

	void Apply(ID3D11DeviceContext* pImmediateContext, int iSlot) const
	{
		pImmediateContext->PSSetShaderResources(iSlot, 1, &m_pTexSRV);
	}

	bool Load(ID3D11Device* pDevice, 
				std::wstring filename);
	bool Release();
};
class TextureMgr
{
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	using MyList = std::map<std::wstring, Texture*>;
public:
	static TextureMgr& GetInstance()
	{
		static TextureMgr input;
		return input;
	}
	MyList m_list;
public:
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	bool Release();
	const Texture* Load(std::wstring szFilepath);
	const Texture* GetPtr(std::wstring key);
	bool Get(std::wstring key,
			Texture& ret);

private:
	TextureMgr();
public:
	virtual ~TextureMgr();

};

#define I_Tex TextureMgr::GetInstance()