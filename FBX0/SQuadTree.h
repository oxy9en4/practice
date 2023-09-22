#pragma once
#include "HeightMap.h"


class SNode
{
public:
	bool m_bLeaf;
	DWORD m_dwDepth;
	T_BOX m_tBox;
	std::vector<DWORD> m_Corner;
	SNode* m_pParent;
	std::vector<SNode*> m_pChild;
	virtual ~SNode()
	{
		m_Corner.clear(); // why m_Corner need to be cleared?
	}
};

class SQuadTree
{
public:
	HeightMap* m_pHeightMap;
	SNode* m_pRootNode;
	bool Build(HeightMap* map);
	SNode* CreateNode(SNode* pParent,
		DWORD dwTL, DWORD dwTR,
		DWORD dwBL, DWORD dwBR);
	void ComputeBoundingBox(SNode* pNode);
	TVector2 GetHeightFromNode(SNode* pNode);

};

