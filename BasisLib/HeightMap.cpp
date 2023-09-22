#include "HeightMap.h"
#include "WICTextureLoader.h"
#pragma comment (lib, "DirectXTK_D.lib")


bool HeightMap::CreateHeightMap(std::wstring hPath)
{
	HRESULT hr;

	ID3D11ShaderResourceView* hView = nullptr;
	ComPtr<ID3D11Resource> texture;
	size_t maxSize = 0;

	if (FAILED(hr = DirectX::CreateWICTextureFromFileEx(m_pDevice,
		hPath.c_str(),
		maxSize,
		D3D11_USAGE_STAGING,
		0,
		D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ,
		0,
		DirectX::WIC_LOADER_DEFAULT,
		texture.GetAddressOf(), nullptr)))
	{
		return false;
	}
	ID3D11Texture2D* tex2D = NULL;
	if (FAILED(texture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&tex2D)))
	{
		false;
	}

	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);

	UINT rSize = desc.Height * desc.Width;
	m_heightList.resize(rSize);

	if (tex2D)
	{
		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(m_pImmediateContext->Map((ID3D11Resource*)tex2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MappedFaceDest)))
		{
			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
			for (UINT row = 0; row < desc.Height; row++)
			{
				UINT rowStart = row * MappedFaceDest.RowPitch;
				for (UINT col = 0; col < desc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					UINT dSize = row * desc.Width + col;
					m_heightList[dSize] = (float)uRed;
				}
			}
			m_pImmediateContext->Unmap(tex2D, D3D11CalcSubresource(0, 0, 1));
		}
	}


	m_iNumRows = desc.Height;
	m_iNumCols = desc.Width;
	tex2D->Release();

	_isHeightLoad = true;

	return true;
}

float HeightMap::GetHeightOfVertex(UINT iVertexIndex)
{
	return m_heightList[iVertexIndex] * 0.25f;
}

bool HeightMap::CreateHeightVertexData()
{
	if (m_VertexList.size() > 0)
	{
		m_VertexList.clear();
	}
	UINT rSize = m_iNumCols * m_iNumRows;
	m_VertexList.resize(rSize);

	float fHalfCols = (m_iNumCols - 1) * 0.5f;
	float fHalfRows = (m_iNumRows - 1) * 0.5f;

	m_iNumCellRows = (m_iNumRows - 1);
	m_iNumCellCols = (m_iNumCols - 1);

	m_iNumFace = m_iNumCellRows * m_iNumCellCols * 2;

	float tx0ffsetU = 1.0f / m_iNumCellCols;
	float txOffsetV = 1.0f / m_iNumCellRows;

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int  iVertexIndex = iRow * m_iNumCols + iCol;
			m_VertexList[iVertexIndex].p.x = (iCol - fHalfCols) * 1.0f;
			m_VertexList[iVertexIndex].p.z = -((iRow - fHalfRows) * 1.0f);
			m_VertexList[iVertexIndex].p.y = GetHeightOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].n = GetNormalOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].c = GetColorOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].t = GetTextureOfVertex(iRow, iCol);
		}
	}

	return true;
}

bool HeightMap::CreateIndexData()
{
	UINT iSize = m_iNumFace * 3;
	m_IndexList.resize(m_iNumFace * 3);

	int iCurIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			//0	1    4   
			//2	   3 5
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_IndexList[iCurIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iCurIndex + 1] = iRow * m_iNumCols + iNextCol;
			m_IndexList[iCurIndex + 2] = iNextRow * m_iNumCols + iCol;
			m_IndexList[iCurIndex + 3] = m_IndexList[iCurIndex + 2];
			m_IndexList[iCurIndex + 4] = m_IndexList[iCurIndex + 1];
			m_IndexList[iCurIndex + 5] = iNextRow * m_iNumCols + iNextCol;

			iCurIndex += 6;
		}
	}
	return true;
}

bool HeightMap::LoadHeightMap(std::wstring texFileName, std::wstring shaderFileName)
{
	if (_isHeightLoad)
	{
		CreateConstantBuffer();
		CreateHeightVertexData();
		CreateIndexData();
		CreateVertexBuffer();
		CreateIndexBuffer();
		m_pShader = I_Shader.Load(shaderFileName);
		CreateInputLayout();
		m_pTex = I_Tex.Load(texFileName);
		UpdateMatrix();
		return true;
	}


	return false;
}
