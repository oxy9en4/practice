#pragma once
#include "Node.h"


class Octree
{
public:
	Node* mpRootNode = nullptr;
	int iNumCounter = -1;
	std::set<Object> mStaticObjectList;
	std::set<Object> mDynamicObjectList;

	void Run();
	void BuildTree(Node* pParent);
	Node* CreateNode(Node* pParent, 
		float x, float y, float z,
		float w, float h, float d);
	Node* CreateNode(Node* pParent,
		Vector3 p,
		float w, float h, float d);
	Node* CreateNode(Node* pParent,
		Vector3 p,
		Vector3 size);

	//
	Node* FindNode(Node* pNode, Object* obj);
	Node* AddStaticObject(Object* obj);
	Node* AddDynamicObject(Object* obj);
	
	// ¼øÈ¸
	std::queue<Node*> Queue;
	void PreOrder(Node* pNode);
	void LevelOrder(Node* pNode);

	bool Init();
	bool PreFrame();
	bool Frame();
	bool PostFrame();
	bool Render();
	bool Release();

	Octree();
	virtual ~Octree();

};