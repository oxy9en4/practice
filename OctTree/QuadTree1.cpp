#include "stdafx.h"
#include "sTree.h"
std::vector<sObject*> StaticObjectList;
std::vector<sObject*> DynamicObjectList;

void SetStaticObject(sTree& sSO) {
	for (int i = 0; i < 3; ++i) {
		sObject* obj = new sStaticObject();
		obj->csName = L"StaticObj";
		obj->csName += std::to_wstring(i);
		obj->Position = { (float)(rand() % 800), (float)(rand() % 600) };
		sSO.AddObject(obj);
		StaticObjectList.push_back(obj);
	}
}
void SetDynamicObject(sTree& sDO) {
	for (int i = 0; i < 3; ++i) {
		sObject* obj = new sDynamicObject();
		obj->csName = L"DynamicObj";
		obj->csName += std::to_wstring(i);
		obj->Position = { (float)(rand() % 800), (float)(rand() % 600) };
		sPoint trgt = {  (float)randstep(0, 0), 
                     (float)randstep(0, 0) };
		obj->SetTarget(trgt);
		sDO.AddObject(obj);
		DynamicObjectList.push_back(obj);
	}
}
int main() {
	sTree quadtree;
	quadtree.run();
	SetStaticObject(quadtree);
	SetDynamicObject(quadtree);
	
	
	int iMaxFrame = 30;
	while (--iMaxFrame > 0) {
		for (int i = 0; i < DynamicObjectList.size(); ++i) {
			sObject* obj = DynamicObjectList[i];
			obj->Move();
		}
		system("cls");
		std::cout << std::endl;
		std::cout << "[" << iMaxFrame << "]" << "Object inform\n";
		quadtree.LevelOrder(quadtree.getRoot());
		Sleep(1000);
	}

	std::cout << std::endl;
	std::cout << "Object inform!\n";
	quadtree.LevelOrder(quadtree.getRoot());
	
	for (int i = 0; i < StaticObjectList.size(); ++i) {
		delete StaticObjectList[i];
	}
	DynamicObjectList.clear();
	for (int i = 0; i < DynamicObjectList.size(); ++i) {
		delete DynamicObjectList[i];
	}
	DynamicObjectList.clear();
}