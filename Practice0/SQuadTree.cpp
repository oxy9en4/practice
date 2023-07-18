#include "stdafx.h"
#include "SQuadTree.h"

SNode* SQuadTree::GetRootNode() {
	return mpRootNode;
}

void SQuadTree::Run() {
	mpRootNode = new SNode(nullptr, 0, 0, 800, 600);
	BuildTree(mpRootNode);
}

void SQuadTree::BuildTree(SNode* pNode) {
	if (pNode->miDepth > 1) return;
	// make 4 children. defin each child's rect
	SNode* pNewNode = CreateNode(pNode,
		pNode->mRct.mPoint[0].x,
		pNode->mRct.mPoint[0].y,
		pNode->mRct.mHalf.x,
		pNode->mRct.mHalf.y);
	pNode->mpChild.push_back(pNewNode);

	pNewNode = CreateNode(pNode,
		pNode->mRct.mPoint[2].x,
		pNode->mRct.mPoint[0].y,
		pNode->mRct.mHalf.x,
		pNode->mRct.mHalf.y);
	pNode->mpChild.push_back(pNewNode);

	pNewNode = CreateNode(pNode,
		pNode->mRct.mPoint[2].x,
		pNode->mRct.mPoint[2].y,
		pNode->mRct.mHalf.x,
		pNode->mRct.mHalf.y);
	pNode->mpChild.push_back(pNewNode);

	pNewNode = CreateNode(pNode,
		pNode->mRct.mPoint[0].x,
		pNode->mRct.mPoint[2].y,
		pNode->mRct.mHalf.x,
		pNode->mRct.mHalf.y);
	pNode->mpChild.push_back(pNewNode);

	std::cout << "[" << pNode->miDepth << "]"
		<< pNode->mRct.mFx << ","
		<< pNode->mRct.mFy << ","
		<< pNode->mRct.mFWidth << ","
		<< pNode->mRct.mFHeight << std::endl;

	for (int i = 0; i < pNode->mpChild.size(); ++i) {
		BuildTree(pNode->mpChild[i]);
	}
}
SNode* SQuadTree::CreateNode(SNode* pParent, float x, float y, float w, float h) {
	SNode* pNode = new SNode(pParent, x, y, w, h);
	pNode->miIndex = miNumNodeCounter++;
	mDynamicNodeList.push_back(pNode);
	return pNode;
}
SNode* SQuadTree::FindNode(SNode* pNode, SObject* obj) {
	if (pNode == nullptr) return nullptr;
	do {
		for (int i = 0; i < pNode->mpChild.size(); ++i) {
			if (pNode->mpChild[i] != nullptr) {
				if (pNode->mRct.RectToRect(pNode->mpChild[i]->mRct, obj->mCollisionBox))
				{
					mQueue.push(pNode->mpChild[i]);
					break;
				}
			}
		}
		if (mQueue.empty()) break;
		pNode = mQueue.front();
		mQueue.pop();
	} while (pNode);
	return pNode;
}
SNode* SQuadTree::StaticAddObject(SObject* obj) {
	SNode* pFindNode = FindNode(mpRootNode, obj);
	if (pFindNode != nullptr)
	{
		pFindNode->mStaticObjectList.push_back(obj);
		return pFindNode;
	}
	return nullptr;
}
SNode* SQuadTree::DynamicAddObject(SObject* obj) {
	SNode* pFindNode = FindNode(mpRootNode, obj);
	if (pFindNode != nullptr) {
		pFindNode->mDynamicObjectList.push_back(obj);
		mDynamicObjectNodeList.insert(pFindNode);
		return pFindNode;
	}
	return nullptr;
}