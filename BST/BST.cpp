#include <iostream>
#include <queue>



struct sNode {
	int iValue;
	sNode* pChild[2] = {};
	sNode(int i) : iValue(i) {}
};

sNode* g_pRootNode = nullptr;
int g_iData[] = { 50, 76, 21 , 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80 };
int g_iIndex;

void AddNode(sNode* pParentNode, sNode* pNewNode) {
	bool b = pParentNode->iValue < pNewNode->iValue;
	if (!pParentNode->pChild[b]) {
		pParentNode->pChild[b] = pNewNode;
		return;
	}
	AddNode(pParentNode->pChild[b], pNewNode);
}

sNode* Find(sNode* pParentNode, int value) {
	bool b = pParentNode->iValue < value;
	if (pParentNode->iValue == value)
		return pParentNode;
	Find(pParentNode->pChild[b], value);
}

void PreOrder(sNode* target) {  //  P L R
	if (!target) return;
	std::cout << target->iValue << " ";
	PreOrder(target->pChild[0]);
	PreOrder(target->pChild[1]);
}
void InOrder(sNode* target) {  //  P L R
	if (!target) return;
	InOrder(target->pChild[0]);
	std::cout << target->iValue << " ";
	InOrder(target->pChild[1]);
}
void PostOrder(sNode* target) { // L R P
	if (!target) return;
	PostOrder(target->pChild[0]);
	PostOrder(target->pChild[1]);
	std::cout << target->iValue << " ";
} 
std::queue<sNode*> que;
void LevelOrder(sNode* target) {
	if (!target) return;

	std::cout << target->iValue << " ";
	
	if(target->pChild[0]) que.push(target->pChild[0]);
	if(target->pChild[1]) que.push(target->pChild[1]);

	if (!que.empty()) {
		target = que.front();
		que.pop();
		LevelOrder(target);
	}
	
}

int main() {
	g_pRootNode = new sNode(g_iData[g_iIndex++]);;
	int iCnt = _countof(g_iData);
	for (int i = 1; i < iCnt; ++i) {
		AddNode(g_pRootNode, new sNode(g_iData[g_iIndex++]));
	}
	

	sNode* tmp = Find(g_pRootNode, g_iData[10]);
	PreOrder(g_pRootNode); std::cout << std::endl;
	InOrder(g_pRootNode); std::cout << std::endl;
	PostOrder(g_pRootNode); std::cout << std::endl;

	LevelOrder(g_pRootNode);
}