#pragma once
#include "Object.h"


class Node
{
public:
	int miIndex = -1;
	int miDepth = 0;
	Box mBox;
	Node* mpParent = nullptr;

	std::vector<Node*> mpChild;
	std::set<Object*> mStaticObjectList;
	std::set<Object*> mDynamicObjectList;

	void SetParent(Node* pParent);
	
	Node(int id);
	Node() = default;
	virtual ~Node();
};