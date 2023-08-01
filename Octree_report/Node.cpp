#include "stdafx.h"
#include "Node.h"

void Node::SetParent(Node* pParent)
{
	if (pParent == nullptr) return;
	mpParent = pParent;
	miDepth = pParent->miDepth + 1;
}

Node::Node(int id) : miIndex(id) {}

Node::~Node()
{
	for (int i = 0; i < 8; ++i) {
		delete mpChild[i];
		mpChild[i] = nullptr;
	}
}
