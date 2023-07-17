#pragma once
#include "sNode.h"

class sTree
{
	std::queue<sNode*> que;
	sNode* RootNode = nullptr;
	int iNumNodeCounter = 0;
	std::set<sNode*> g_DynamicObjectNodeList;
	std::vector<sNode*> g_DynamicNodeList;
public:
	
	sNode* getRoot();
	void run();
	void BuildTree(sNode* pNode);
	sNode* CreateNode(sNode* _pParent, float x, float y, float width, float height);
	sNode* StaticAddObject(sObject* obj);
	sNode* DynamicAddObject(sObject* obj);
	sNode* FindNode(sNode* pNode, sObject* obj);

	bool Init();
	bool PreFrame();
	bool Frame();
	bool PostFrame();
	bool Render();
	bool Release();


	void LevelOrder(sNode* pNode);
	~sTree()
	{
		delete RootNode;
	}
};

