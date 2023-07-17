#pragma once
// cpp의 내용도 모두 헤더파일에 작성할 것. 



template <typename T>
struct Node {
	T* pData;
	Node* pNext;
	Node* pPrev;
};



template <typename T>
class LinkedList{
public:

	Node<T>* pHead;
	Node<T>* pTail;
	Node<T>* NewNode();
	static int iCounter;

	

	LinkedList<T>() : pHead(nullptr), pTail(nullptr) {} // constructor
	~LinkedList<T>(); // destructor

	void Push_Back(const T& pData);
	void RemoveNode(T& pData);
	void TraverseList();
	Node<T>* FindNode(const T& pData);
	void Reset();
	

};

template <typename T>
void LinkedList<T>::Push_Back(const T& pData) {
	Node<T>* node = new Node<T>;
	if (!pHead)
	{
		pHead = node;
		pTail = pHead;
	}
	else
	{
		pTail->pNext = node;
		node->pPrev = pTail;
		pTail = node;
	}
}

template <class T>
void LinkedList<T>::RemoveNode(T& pData)
{
	if (pData == pHead)
	{
		pHead = pData->pNext;
		pData->pNext->pPrev = nullptr;
	}
	else if (pData == pTail)
	{
		pTail = pData->pPrev;
		pData->pPrev->pNext = nullptr;
	}
	else
	{
		pData->pPrev->pNext = pData->pNext;
		pData->pNext->pPrev = pData->pPrev;
	}
	
	delete pData;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	// List의 모든 노드를 삭제
	Node<T>* currNode = pHead;
	while (currNode)
	{
		Node<T>* nextNode = currNode->pNext;
		delete currNode;
		currNode = nextNode;
	}
	pHead = nullptr;
	pTail = nullptr;
}