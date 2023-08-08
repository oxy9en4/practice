#pragma once
#include "Node.h"

using MyList = std::unordered_map<int, Object*>;
extern MyList StaticObjList;
extern MyList DynamicObjList;
extern std::pair<int, int> rtn;
extern bool DToD;

class Octree
{
public:
	Node* mpRootNode = nullptr;
	int iNumCounter = -1;
	std::set<Node*> mNodeList_StaObj;
	std::set<Node*> mNodeList_DynObj;

	std::vector<Node*> NodeIndex;

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
	bool AddStaticObject(Object* obj);
	bool AddDynamicObject(Object* obj);

	bool CheckCollision(Object* obj);
	
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