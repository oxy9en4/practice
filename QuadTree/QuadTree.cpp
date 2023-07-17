#include <iostream>
#include <vector>
#include <queue>
enum { NTree = 4 };

struct sNode {
	int iValue = -1;
	int iDepth = 0;
	sNode* pParent = nullptr;
	std::vector<sNode*> pChild;
	sNode(int i) : iValue(i) {}

	void setParent(sNode* pPar) {
		pParent = pPar;
		iDepth = pPar->iDepth + 1;
	}
};


sNode* g_pRootNode = nullptr;
int iCounter = 0;

void AddNode(sNode* pNode) {
	if (pNode->iDepth > 1) return;
	for (int i = 0; i < NTree; ++i) {
		sNode* pNewNode = new sNode(iCounter++);
		pNewNode->setParent(pNode);
		pNode->pChild.push_back(pNewNode);
	}
	for (int i = 0; i < NTree; ++i) {
		AddNode(pNode->pChild[i]);
	}
}

void PreOrder(sNode* target) {  //  P L R
	if (!target) return;
	std::cout << target->iValue << " ";
	for (auto a : target->pChild) {
		PreOrder(a);
	}
}

void PostOrder(sNode* target) {  //  P L R
	if (!target) return;
	for (auto a : target->pChild) {
		PreOrder(a);
	}
	std::cout << target->iValue << " ";
}

std::queue<sNode*> que;
void LevelOrder(sNode* target) {
	if (!target) return;  // this doesn't work lol
	std::cout << target->iValue << " ";
	for (auto a : target->pChild) {
		if (a) que.push(a);
	}
	if (!que.empty()) {  // »Ï...
		target = que.front();
		que.pop();
		LevelOrder(target);
	}
}

void BuildTree() {
	g_pRootNode = new sNode(iCounter++);
	AddNode(g_pRootNode);
}


int main() {
	BuildTree();


	PreOrder(g_pRootNode); std::cout << std::endl;
	PostOrder(g_pRootNode); std::cout << std::endl;
	LevelOrder(g_pRootNode); std::cout << std::endl;
}