#include "stdafx.h"
#include "TextureMgr.h"

bool Texture::Load(ID3D11Device* pDevice, std::wstring filename)
{
	auto imageobj = std::make_unique<DirectX::ScratchImage>();
	DirectX::TexMetadata metadata;

	HRESULT hr = DirectX::GetMetadataFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, metadata);
	if (SUCCEEDED(hr))
	{
		hr = DirectX::LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, *imageobj);
		if (SUCCEEDED(hr))
		{
			hr = DirectX::CreateShaderResourceView(pDevice, imageobj->GetImages(), imageobj->GetImageCount(), metadata, &m_pTexSRV);
			if (SUCCEEDED(hr))
			{
				return true;
			}
		}
	}
	hr = DirectX::GetMetadataFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, metadata);
	if (SUCCEEDED(hr))
	{
		hr = DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, *imageobj);
		if (SUCCEEDED(hr))
		{
			hr = DirectX::CreateShaderResourceView(pDevice, imageobj->GetImages(), imageobj->GetImageCount(), metadata, &m_pTexSRV);
			if (SUCCEEDED(hr))
			{
				return true;
			}
		}
	}
	hr = DirectX::GetMetadataFromTGAFile(filename.c_str(), DirectX::TGA_FLAGS_NONE, metadata);
	if (SUCCEEDED(hr))
	{
		hr = DirectX::LoadFromTGAFile(filename.c_str(), DirectX::TGA_FLAGS_NONE, &metadata, *imageobj);
		if (SUCCEEDED(hr))
		{
			hr = DirectX::CreateShaderResourceView(pDevice, imageobj->GetImages(), imageobj->GetImageCount(), metadata, &m_pTexSRV);
			if (SUCCEEDED(hr))
			{
				return true;
			}
		}
	}
	return false;
}

bool Texture::Release()
{
	if (m_pTexSRV) m_pTexSRV->Release();
	m_pTexSRV = nullptr;
	return true;
}

void TextureMgr::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pDevice = pDevice;
	m_pImmediateContext = pImmediateContext;
}

bool TextureMgr::Release()
{
	for (auto& data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
	return true;
}

const Texture* TextureMgr::Load(std::wstring szFullFilepath)
{
	std::size_t found = szFullFilepath.find_last_of(L"/");
	std::wstring path = szFullFilepath.substr(0, found + 1);
	std::wstring key = szFullFilepath.substr(found + 1);
	const Texture* data = GetPtr(key);
	if (data != nullptr) return data;
	Texture* newData = new Texture;
	if (newData->Load(m_pDevice, szFullFilepath))
	{
		m_list.insert(std::make_pair(key, newData));
		return newData;
	}
	delete newData;
	return nullptr;
}

const Texture* TextureMgr::GetPtr(std::wstring key)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter) return nullptr;
	return iter->second;
}

bool TextureMgr::Get(std::wstring key, Texture& ret)
{
	auto iter = m_list.find(key);
	if (m_list.end() == iter) return false;
	ret = *(iter->second);
	return false;
}

TextureMgr::TextureMgr()
{
}

TextureMgr::~TextureMgr()
{
	for (auto& data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
}
