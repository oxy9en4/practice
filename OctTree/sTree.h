#pragma once
#include "sNode.h"

class sTree
{
	std::queue<sNode*> que;
	sNode* RootNode;
public:
	
	sNode* getRoot();
	void run();
	void BuildTree(sNode* pNode);
	sNode* CreateNode(sNode* _pParent, float x, float y, float width, float height);
	sNode* AddObject(sObject* obj);
	sNode* FindNode(sNode* pNode, sObject* obj);


	void LevelOrder(sNode* pNode);
	~sTree()
	{
		delete RootNode;
	}
};

