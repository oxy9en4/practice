#pragma once
#include "SNode.h"

class SQuadTree
{
public:
	std::queue<SNode*> mQueue;
	SNode* mpRootNode = nullptr;
	int miNumNodeCounter = 0;
	std::set<SNode*> mDynamicObjectNodeList;
	std::vector<SNode*> mDynamicNodeList;

	SNode* GetRootNode();

	
	void BuildTree(SNode* pNode);
	SNode* CreateNode(SNode* pParent,
		float x,
		float y,
		float w,
		float h);
	SNode* FindNode(SNode* pNode, SObject* obj);
	SNode* StaticAddObject(SObject* obj);
	SNode* DynamicAddObject(SObject* obj);
	void Run();


	~SQuadTree() {
		delete mpRootNode;
	}
};

