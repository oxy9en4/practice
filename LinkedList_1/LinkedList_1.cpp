#include <stdio.h>
#include <stdlib.h>

typedef struct TNode TNode;

//전위연결리스트로 변경하라. 단방향 구현


struct TNode
{
	int iID;
	int iValue;
	TNode* pNext;
};
TNode* Create();
void Link(TNode* pNewNode);
void Print();

TNode g_head = { -1, -1, NULL };
int g_iCounter = 0;


int main()
{
	int input = 0;
	for (int i = 0; i < 3; i++)
	{
		TNode* pNewNode = Create();
		Link(pNewNode);
		
	}
	Print();
	TNode* pNode = g_head.pNext;
	while (pNode != NULL)
	{
		TNode* pTemp = pNode->pNext;
		free(pNode);
		pNode = pTemp;
	}

}

TNode* Create()
{
	TNode* node = (TNode*)malloc(sizeof(TNode));
	if (node != NULL)
	{
		node->iID = g_iCounter++;
		node->iValue = g_iCounter * 10;
		node->pNext = NULL;
	}
	return node;
}

void Link(TNode* pNewNode)
{
	pNewNode->pNext = g_head.pNext;
	g_head.pNext = pNewNode;
	
}

void Print()
{

	for (TNode* pNode = g_head.pNext; pNode != NULL; pNode = pNode->pNext)
		printf("%d ", pNode->iValue);
}
