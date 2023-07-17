#include "stdafx.h"
#include "sTree.h"


sNode* sTree::getRoot() {
	return RootNode;
}

void sTree::run() {
	RootNode = new sNode(nullptr, 0, 0, 800, 600);
	BuildTree(RootNode);
}

void sTree::BuildTree(sNode* pNode) {
	if (pNode->iDepth > Max_Depth) return; // escape condition
	sPoint vTC = { pNode->rt.Center.x, pNode->rt.fy };
	sPoint vRC = { pNode->rt.Point[2].x, pNode->rt.Center.y };
	sPoint vBC = { pNode->rt.Center.x, pNode->rt.Point[2].y };
	sPoint vLC = { pNode->rt.fx, pNode->rt.Center.y };

	sNode* pNewNode = CreateNode(pNode,
		pNode->rt.fx,
		pNode->rt.fy,
		pNode->rt.Half.x,
		pNode->rt.Half.y);
	pNode->pChild.push_back(pNewNode);
	pNewNode = CreateNode(pNode,
		vTC.x,
		vTC.y,
		pNode->rt.Half.x,
		pNode->rt.Half.y);
	pNode->pChild.push_back(pNewNode);
	pNewNode = CreateNode(pNode,
		pNode->rt.Center.x,
		pNode->rt.Center.y,
		pNode->rt.Half.x,
		pNode->rt.Half.y);
	pNode->pChild.push_back(pNewNode);
	pNewNode = CreateNode(pNode,
		vLC.x,
		vLC.y,
		pNode->rt.Half.x,
		pNode->rt.Half.y);
	pNode->pChild.push_back(pNewNode);

	// output for check

	std::cout << "[" << pNode->iDepth << "]" << "("
		<< pNode->rt.fx << ", "
		<< pNode->rt.fy << ", "
		<< pNode->rt.fWidth << ", "
		<< pNode->rt.fHeight << ")" << std::endl;
	for (int i = 0; i < pNode->pChild.size(); ++i) {
		BuildTree(pNode->pChild[i]);
	}
}

sNode* sTree::CreateNode(sNode* _pParent, float x, float y, float width, float height) {
	return new sNode(_pParent, x, y, width, height);
}

sNode* sTree::StaticAddObject(sObject* obj) {
	sNode* pFindNode = FindNode(RootNode, obj);
	if (pFindNode != nullptr)
	{
		pFindNode->StaticObjectList.push_back(obj);
		return pFindNode;
	}
	return nullptr;
}
sNode* sTree::DynamicAddObject(sObject* obj) {
	sNode* pFindNode = FindNode(RootNode, obj);
	if (pFindNode != nullptr)
	{
		pFindNode->DynamicObjectList.push_back(obj);
		g_DynamicObjectNodeList.insert(pFindNode);
		return pFindNode;
	}
	return nullptr;
}

sNode* sTree::FindNode(sNode* pNode, sObject* obj) {
	if (pNode == nullptr) return nullptr;
	do	{
		for (int i = 0; i < pNode->pChild.size(); ++i) {
			if (pNode->pChild[i] != nullptr) {
				if (sCollision::RectToRect
					(pNode->pChild[i]->rt,
					obj->rect))
				{
					que.push(pNode->pChild[i]);
					break;
				}
			}
		}
		if (que.empty()) break;
		pNode = que.front();
		que.pop();
	} while(pNode);
	return pNode;
}

void sTree::LevelOrder(sNode* pNode) {
	if (pNode == nullptr) return;
	std::wcout << L"[" << pNode->iDepth << L"]"
		<< pNode->rt.fx << L","
		<< pNode->rt.fy << L","
		<< pNode->rt.fWidth << L","
		<< pNode->rt.fHeight << L","
		// << pNode->StaticObjectList.size() << std::endl;
		<< pNode->DynamicObjectList.size() << std::endl;
	for (int iobj = 0; iobj < pNode->DynamicObjectList.size(); ++iobj) {
		std::wcout << L"       " << L"<" << iobj << L">"
			<< pNode->DynamicObjectList[iobj]->csName << L"("
			<< pNode->DynamicObjectList[iobj]->Position.x << L","
			<< pNode->DynamicObjectList[iobj]->Position.y << L")" << std::endl;
	}
	for (int i = 0; i < pNode->pChild.size(); ++i) {
		if (pNode->pChild[i] != nullptr)
			que.push(pNode->pChild[i]);
	}
	if (!que.empty()) {
		pNode = que.front();
		que.pop();
		LevelOrder(pNode);
	}
}


bool sTree::Init() {
	return true;
}
bool sTree::PreFrame() {
	for (auto node : g_DynamicObjectNodeList) {
		node->DynamicObjectList.clear();
	}
	return true;
}
bool sTree::Frame() {
	return true;
}
bool sTree::PostFrame() {
	return true;
}
bool sTree::Render() {
	return true;
}
bool sTree::Release() {
	return true;
}