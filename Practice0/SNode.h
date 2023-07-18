#pragma once
#include "SObject.h"



class SNode
{
public:
	SNode* mpParent = nullptr;
	std::vector<SNode*> mpChild;
	int miDepth = 0;
	int miIndex = 0;
	SRect mRct;
	std::vector<SObject*> mStaticObjectList;
	std::vector<SObject*> mDynamicObjectList;
	
	void SetParent(SNode* pParent) {
		if (pParent == nullptr) return;
		mpParent = pParent;
		miDepth = pParent->miDepth + 1;
	}

	SNode(SNode* pParent,
		float x,
		float y,
		float w,
		float h) 
	{
		mRct.Set(x, y, w, h);
		SetParent(pParent);
	}
	SNode();
	~SNode() {
		if (mpChild.size() != 0) {
			delete mpChild[0];
			delete mpChild[1];
			delete mpChild[2];
			delete mpChild[3];
		}
	}
};

