#pragma once
#include "Node.h"


class Octree
{
public:
	Node* mpRootNode = nullptr;
	int iNumCounter = -1;
	std::vector<Object> StaticObjectList;
	std::vector<Object> DynamicObjectList;

	void Run();
	void BuildTree(Node* pParent);
	Node* CreateNode(Node* pParent, 
		float x, float y, float z,
		float w, float h, float d);

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