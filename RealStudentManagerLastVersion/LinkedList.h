#pragma once

template <class T>
struct Node {
	T* pData;
	Node<T>* pNext;
	Node<T>* pPrev;

	Node<T>(T* t) : pData(t), pNext(nullptr), pPrev(nullptr) {}  // 持失切
};


template <class T>
class LinkedList
{
public:
	Node<T>* pHead;
	Node<T>* pTail;

	int size = 0;

	LinkedList() : pHead(nullptr), pTail(nullptr), size(0) {} // 持失切
	
	bool removeByID(int id);
	void Push_Back(T* s);
	void clear();
	void print();
	T* searchByName(const string& name);
	T* searchByID(const int& id);
	void sortByName();
	void sortByID();
	void sortByScore();
};

template <class T>
bool LinkedList<T>::removeByID(int id) {
	Node<T>* curr = pHead;
	while (curr) {
		if (curr->pData->id == id) {
			if (curr->pNext) curr->pNext->pPrev = curr->pPrev;
			if (curr->pPrev) curr->pPrev->pNext = curr->pNext;
			delete curr->pData;
			delete curr;
			--size;
			return true;
		}
		curr = curr->pNext;
	}
	return false;
}

template <class T>
void LinkedList<T>::Push_Back(T* s){
	Node<T>* newNode = new Node<T>(s);
	if (!pHead) {
		pHead = pTail = newNode;
	}
	else
	{
		pTail->pNext = newNode;
		newNode->pPrev = pTail;
		pTail = newNode;
	}
	++size;
}

template <class T>
void LinkedList<T>::clear() {
	Node<T>* curr = pHead;
	while (curr) {
		Node<T>* next = curr->pNext;
		delete curr->pData;
		delete curr;
		curr = next;
	}
	pHead = pTail = nullptr;
	size = 0;
}

template <class T>
void LinkedList<T>::print() {
	Node<T>* curr = pHead;
	while (curr) {
		curr->pData->print();
		curr = curr->pNext;
	}
}

template <class T>
T* LinkedList<T>::searchByName(const string& name) {
	Node<T>* curr = pHead;
	while (curr) {
		if (curr->pData->name == name) {
			return curr->pData;
		}
		curr = curr->pNext;
	}
	return NULL;
}

template <class T>
T* LinkedList<T>::searchByID(const int& id) {
	Node<T>* curr = pHead;
	while (curr) {
		if (curr->pData->id == id) {
			return curr->pData;
		}
		curr = curr->pNext;
	}
	return NULL;
}

template <class T>
void LinkedList<T>::sortByName() {
	if (size <= 1) return;

	Node<T>* i, * j, * maxNode;
	for (i = pHead; i != nullptr && i->pNext != nullptr; i = i->pNext) {
		maxNode = i;
		for (j = i->pNext; j != nullptr; j = j->pNext) {
			if (maxNode->pData->name > j->pData->name) {
				maxNode = j;
			}
		}
		if (maxNode != i) {
			swap(i->pData, maxNode->pData);
		}
	}
}


template <class T>
void LinkedList<T>::sortByID() {
	if (size <= 1) return;

	Node<T>* i, * j, * maxNode;
	for (i = pHead; i != nullptr && i->pNext != nullptr; i = i->pNext) {
		maxNode = i;
		for (j = i->pNext; j != nullptr; j = j->pNext) {
			if (maxNode->pData->id > j->pData->id) {
				maxNode = j;
			}
		}
		if (maxNode != i) {
			swap(i->pData, maxNode->pData);
		}
	}
}


template <class T>
void LinkedList<T>::sortByScore() {
	if (size <= 1) return;

	Node<T>* i, * j, * maxNode;
	for (i = pHead; i != nullptr && i->pNext != nullptr; i = i->pNext) {
		maxNode = i;
		for (j = i->pNext; j != nullptr; j = j->pNext) {
			if (maxNode->pData->total < j->pData->total) {
				maxNode = j;
			}
		}
		if (maxNode != i) {
			swap(i->pData, maxNode->pData);
		}
	}
}
