#include "stdafx.h"
#include "Octree.h"

MyList StaticObjList;
MyList DynamicObjList;
std::pair<int, int> rtn = { -1, -1 };

void Octree::Run()
{
	BuildTree(mpRootNode); // BuildTree is recursive func.

	// Indexing

	NodeIndex.push_back(mpRootNode);
	LevelOrder(mpRootNode);

}

void Octree::BuildTree(Node* pParent)
{
	if (pParent->miDepth > 0) return; // Escape condition by Depth


	for (int i = 0; i < 8; ++i) {
		Vector3& vHalf = pParent->mBox.mHalf;

		float Width = 0.0f, Height = 0.0f, Depth = 0.0f;
		if ((i % 4) != 3 && (i % 4) != 0) Width = vHalf.x;
		if (i % 4 > 1) Height = vHalf.y;
		if (i > 3) Depth = vHalf.z;
		Vector3 fSize(Width, Height, Depth);

		Node* pNewNode = CreateNode(pParent, pParent->mBox.mPoint[0] / 2 + fSize, vHalf);

		pParent->mpChild.push_back(pNewNode);


		BuildTree(pParent->mpChild[i]);
	}
}

Node* Octree::CreateNode(Node* pParent, float x, float y, float z, float w, float h, float d)
{
	Node* pNode = new Node(++iNumCounter);
	pNode->SetParent(pParent);
	pNode->mBox.Set(x, y, z, w, h, d);
	return pNode;
}

Node* Octree::CreateNode(Node* pParent, Vector3 p, float w, float h, float d)
{
	Node* pNode = new Node(++iNumCounter);
	pNode->SetParent(pParent);
	pNode->mBox.Set(p, w, h, d);
	return pNode;
}

Node* Octree::CreateNode(Node* pParent, Vector3 p, Vector3 size)
{
	Node* pNode = new Node(++iNumCounter);
	pNode->SetParent(pParent);
	pNode->mBox.Set(p, size);
	return pNode;
}

Node* Octree::FindNode(Node* pNode, Object* obj)
{
	if (pNode == nullptr) return nullptr;
	do
	{
		for (int i = 0; i < pNode->mpChild.size(); ++i)
		{
			if (pNode->mpChild[i] != nullptr)
			{
				if (obj->mBox.ToBox(pNode->mpChild[i]->mBox))
				{
					Queue.push(pNode->mpChild[i]);
					break;
				}
			}
		}
		if (Queue.empty()) break;
		pNode = Queue.front();
		Queue.pop();
	} while (pNode);
	return pNode;
}

bool Octree::AddStaticObject(Object* obj)
{
	Node* pFoundNode = FindNode(mpRootNode, obj);
	if (pFoundNode != nullptr)
	{
		obj->iNodeIndex = pFoundNode->miIndex;
		pFoundNode->mStaticObjectList.insert(obj);
		mNodeList_StaObj.insert(pFoundNode);
		return pFoundNode;
	}
	return false;
}

bool Octree::AddDynamicObject(Object* obj)
{
	Node* pFoundNode = FindNode(mpRootNode, obj);
	if (pFoundNode == nullptr) return false;
	if (obj->iNodeIndex != -1)
	{
		if (CheckCollision(obj))
		{
			return true;
		}

	}

	obj->iNodeIndex = pFoundNode->miIndex;
	pFoundNode->mDynamicObjectList.insert(obj);
	mNodeList_DynObj.insert(pFoundNode);
	return false;
}

bool Octree::CheckCollision(Object* obj)
{
	Node* iter = NodeIndex[obj->iNodeIndex];
	
	for (auto target : iter->mDynamicObjectList)
	{
		if (obj->mBox.ToBox(target->mBox)
			&& obj != target)
		{
			iter->mDynamicObjectList.erase(target);
			
			rtn.first = target->iListIndex;
			

			iter->mDynamicObjectList.erase(obj);
			rtn.second = obj->iListIndex;
			

			return true;
			
		}
	}
	return false;
}

void Octree::PreOrder(Node* pNode)
{

	return;
}

void Octree::LevelOrder(Node* pNode)
{
	if (pNode == nullptr) return;

	for (int i = 0; i < pNode->mpChild.size(); ++i)
	{
		if (pNode->mpChild[i] != nullptr)
		{
			Queue.push(pNode->mpChild[i]);
			NodeIndex.push_back(pNode->mpChild[i]);
		}
	}
	if (!Queue.empty())
	{
		Node* pNode = Queue.front();
		Queue.pop();
		LevelOrder(pNode);
	}
}

bool Octree::Init()
{
	return true;
}

bool Octree::PreFrame()
{
	for (auto node : mNodeList_DynObj)
	{
		node->mDynamicObjectList.clear();
	}
	mNodeList_DynObj.clear();

	return false;
}

bool Octree::Frame()
{
	return true;
}

bool Octree::PostFrame()
{
	return true;
}

bool Octree::Render()
{
	/*if (pNode == nullptr) return;
	std::wcout << L"[" << pNode->miDepth << L"]"
		<< pNode->mBox.v.x << L", "
		<< pNode->mBox.v.y << L", "
		<< pNode->mBox.v.z << L", "
		<< pNode->mBox.size.x << L", "
		<< pNode->mBox.size.y << L", "
		<< pNode->mBox.size.z << L", "
		<< pNode->mStaticObjectList.size() << L", "
		<< pNode->mDynamicObjectList.size() << std::endl;

	for (int iobj = 0; iobj < pNode->mDynamicObjectList.size(); ++iobj)
	{
		std::wcout << "          " << L"<" << iobj << L">"
			<< pNode->mDynamicObjectList[iobj]->wsName << L", "
			<< pNode->mDynamicObjectList[iobj]->mBox.v.x << L", "
			<< pNode->mDynamicObjectList[iobj]->mBox.v.y << L", "
			<< pNode->mDynamicObjectList[iobj]->mBox.v.z << std::endl;
	}
	for (int i = 0; i < pNode->mpChild.size(); ++i)
	{
		if (pNode->mpChild[i] != nullptr)
		{
			Queue.push(pNode->mpChild[i]);
		}
	}
	if (!Queue.empty())
	{
		Node* pNode = Queue.front();
		Queue.pop();
		LevelOrder(pNode);
	}*/
	return true;
}

bool Octree::Release()
{
	return true;
}

Octree::Octree()
{
}

Octree::~Octree()
{
}
