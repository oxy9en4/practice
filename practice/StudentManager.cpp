#include "stdafx.h"
#include "StudentManager.h"


template <typename T>
void StudentManager<T>::AddRandomly() {
	for (int i = 0; i < 10; ++i) {
		m_LinkedList.NewNode();
	}
}