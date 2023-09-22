#include "SQuadTree.h"

bool SQuadTree::Build(HeightMap* map)
{
	m_pHeightMap = map; // pattern 1. get parameter and put in member variable
	DWORD dwX = m_pHeightMap->m_iNumCols;
	DWORD dwY = m_pHeightMap->m_iNumRows;
	m_pRootNode = CreateNode(nullptr,
		0, dwX - 1,								// 0�� �»��(TL) dwX - 1�� ����(TR)
		dwX * (dwY - 1), dwX * dwY - 1);		// dwX * dwY-1�� ���ϴ�(BL). ���� 4, 4��� 3 * (4 - 1) �� 12. �׳� 3 * 4 = 12��� ������ ��� �ε���( - 1)
	return true;
}

SNode* SQuadTree::CreateNode(SNode* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{
	SNode* pNode = new SNode;
	pNode->m_Corner.push_back(dwTL);
	pNode->m_Corner.push_back(dwTR);
	pNode->m_Corner.push_back(dwBL);
	pNode->m_Corner.push_back(dwBR);

	ComputeBoundingBox(pNode);
	return pNode;
}

void SQuadTree::ComputeBoundingBox(SNode* pNode)
{
	DWORD dwV0 = pNode->m_Corner[0]; // pNode�� ���� ������� ���. �� ����� Corner 0���� �»� ��ǥ
	DWORD dwV1 = pNode->m_Corner[3]; // Coner 3���� ���� ��ǥ
	TVector2 vHeight = GetHeightFromNode(pNode);  // literally get height from node
	pNode->m_tBox.vMax.x = m_pHeightMap->m_VertexList[dwV1].p.x; // ��� Box�� Max x��ǥ�� map�� VertexList[���ϴ�]�� x��ǥ
	pNode->m_tBox.vMax.z = m_pHeightMap->m_VertexList[dwV0].p.z; // max z��ǥ�� VertexList[�»��]
	pNode->m_tBox.vMin.x = m_pHeightMap->m_VertexList[dwV1].p.x;
	pNode->m_tBox.vMin.z = m_pHeightMap->m_VertexList[dwV0].p.z;

	pNode->m_tBox.vMax.y = vHeight.x;
	pNode->m_tBox.vMin.y = vHeight.y;
	pNode->m_tBox.vAxis[0] = { 1,0,0 };
	pNode->m_tBox.vAxis[1] = { 0,1,0 };
	pNode->m_tBox.vAxis[2] = { 0,0,1 };

	pNode->m_tBox.vCenter = (pNode->m_tBox.vMax + pNode->m_tBox.vMin) * 0.5;
	pNode->m_tBox.fExtent[0] = pNode->m_tBox.vMax.x - pNode->m_tBox.vCenter.x;
	pNode->m_tBox.fExtent[1] = pNode->m_tBox.vMax.y - pNode->m_tBox.vCenter.y;
	pNode->m_tBox.fExtent[2] = pNode->m_tBox.vMax.z - pNode->m_tBox.vCenter.z;
}

TVector2 SQuadTree::GetHeightFromNode(SNode* pNode)
{
	DWORD dwTL = pNode->m_Corner[0];
	DWORD dwTR = pNode->m_Corner[1];
	DWORD dwBL = pNode->m_Corner[2];
	DWORD dwBR = pNode->m_Corner[3];

	DWORD dwStartCol = dwTL % m_pHeightMap->m_iNumCols;
	DWORD dwEndCol = dwTR % m_pHeightMap->m_iNumCols;
	DWORD dwStartRow = dwTL / m_pHeightMap->m_iNumCols;
	DWORD dwEndRow = dwBL / m_pHeightMap->m_iNumCols;

	TVector2 vHeight;
	vHeight.x = -FLT_MAX;
	vHeight.y = FLT_MAX;

	for (int dwRow = dwStartRow; dwRow <= dwEndRow; dwRow++)
	{
		for (int dwCol = dwStartCol; dwCol <= dwEndCol; dwCol++)
		{
			DWORD dwCurrent = dwRow * m_pHeightMap->m_iNumCellCols + dwCol;
			if (m_pHeightMap->m_VertexList[dwCurrent].p.y > vHeight.x)
			{
				vHeight.x = m_pHeightMap->m_VertexList[dwCurrent].p.y;
			}
			if (m_pHeightMap->m_VertexList[dwCurrent].p.y < vHeight.y)
			{
				vHeight.y = m_pHeightMap->m_VertexList[dwCurrent].p.y;
			}
		}
	}

	return vHeight;
}
