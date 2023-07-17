#include "stdafx.h"
#include "sTree.h"
#include "sTimer.h"
std::vector<sObject*> StaticObjectList;
std::vector<sObject*> DynamicObjectList;

void SetStaticObject(sTree& sSO) {
	for (int i = 0; i < 3; ++i) {
		sStaticObject* obj = new sStaticObject();
		obj->csName = L"StaticObj";
		obj->csName += std::to_wstring(i);
		obj->Position = { (float)(rand() % 800), (float)(rand() % 600) };
		sSO.StaticAddObject(obj);
		StaticObjectList.push_back(obj);
	}
}
void SetDynamicObject(sTree& sDO) {
	for (int i = 0; i < 3; ++i) {
		sObject* obj = new sDynamicObject();

		obj->csName = L"DynamicObj";
		obj->csName += std::to_wstring(i);
		obj->Position = { (float)(rand() % 800), (float)(rand() % 600) };
		obj->SetRect(obj->Position, 
			(float)((rand()%10)+1.0f),
			(float)((rand() % 10) + 1.0f));
		sPoint trgt = {  (float)randstep(0, 800), 
                     (float)randstep(0, 600) };
		obj->SetTarget(trgt);		
		sDO.DynamicAddObject(obj);
		DynamicObjectList.push_back(obj);
	}
}
int main() {
	sTree quadtree;
	sTimer timer;
	quadtree.run();
	SetStaticObject(quadtree);
	SetDynamicObject(quadtree);

	timer.Init();
	while (timer._fGameTimer < 100) {
		timer.Frame();
		quadtree.PreFrame();
		for (int i = 0; i < DynamicObjectList.size(); ++i) {
			sObject* obj = DynamicObjectList[i];
			obj->Move(timer._fSPF);
			quadtree.DynamicAddObject(obj);
		}
		system("cls");
		std::cout << std::endl;
		quadtree.LevelOrder(quadtree.getRoot());
		timer.Render();
		Sleep(100);
	}

	timer.Release();
	
	for (int i = 0; i < StaticObjectList.size(); ++i) {
		delete StaticObjectList[i];
	}
	DynamicObjectList.clear();
	for (int i = 0; i < DynamicObjectList.size(); ++i) {
		delete DynamicObjectList[i];
	}
	DynamicObjectList.clear();
}