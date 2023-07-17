#pragma once
#include "sObject.h"
class sNode
{
public:
	int iIndex;
	sRect rt;
	int iDepth = 0;
	sNode* pParent = nullptr;
	std::vector<sNode*> pChild;
	std::vector<sObject*> StaticObjectList;
	std::vector<sObject*> DynamicObjectList;

	void setParent(sNode* _pParent) {
		if (_pParent == nullptr) return;
		pParent = _pParent;
		iDepth = _pParent->iDepth + 1;
	}
	sNode(sNode* _pParent,
		float x,
		float y,
		float Width,
		float Height) : pParent(_pParent) {
		rt.Set(x, y, Width, Height);
		setParent(_pParent);
	}
	~sNode()
	{
		if (pChild.size() != 0) {
			delete pChild[0];
			delete pChild[1];
			delete pChild[2];
			delete pChild[3];
		}
	}

};

