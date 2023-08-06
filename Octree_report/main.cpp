#include "stdafx.h"
#include "Octree.h"
#include "Timer.h"



void SetStaticObj(Octree& tree)
{
	if (tree.mpRootNode == nullptr) return;
	
	int iMaxWidth = tree.mpRootNode->mBox.size.x;
	int iMaxHeight = tree.mpRootNode->mBox.size.y;
	int iMaxDepth = tree.mpRootNode->mBox.size.z;

	for (int i = 0; i < 1; ++i) {
		Object* obj = new StaticObject();
		obj->wsName = L"StaticObj";
		obj->wsName += std::to_wstring(i);
		obj->mBox.v = { (float)(rand() % iMaxWidth),
						(float)(rand() % iMaxHeight),
						(float)(rand() % iMaxDepth) };
		obj->SetBox(obj->mBox.v,
					(float)((rand() % 10) + 10.0f),
					(float)((rand() % 10) + 10.0f),
					(float)((rand() % 10) + 10.0f));
		if (!tree.AddStaticObject(obj))
		{
			obj->iListIndex = i;
			StaticObjList.insert(std::make_pair(i, obj));
		}
		
	}
}

void SetDynamicObj(Octree& tree)
{
	if (tree.mpRootNode == nullptr) return;

	int iMaxWidth = tree.mpRootNode->mBox.size.x;
	int iMaxHeight = tree.mpRootNode->mBox.size.y;
	int iMaxDepth = tree.mpRootNode->mBox.size.z;

	for (int i = 0; i < 10; ++i) {
		Object* obj = new DynamicObject();
		obj->wsName = L"DynamicObj";
		obj->wsName += std::to_wstring(i);
		obj->mBox.v = { (float)(rand() % iMaxWidth),
						(float)(rand() % iMaxHeight),
						(float)(rand() % iMaxDepth) };
		obj->SetBox(obj->mBox.v,
			(float)((rand() % 10) + 100.0f),
			(float)((rand() % 10) + 100.0f),
			(float)((rand() % 10) + 100.0f));
		Vector3 target = { (float)randstep(0, iMaxWidth),
							(float)randstep(0, iMaxHeight),
							(float)randstep(0, iMaxDepth) };
		
		obj->SetTarget(target);
		if (!tree.AddDynamicObject(obj))
		{
			obj->iListIndex = i;
			DynamicObjList.insert(std::make_pair(i, obj));
		}
		
	}
}


int main()
{
	bool check = false;
	std::cout.precision(3);
	Octree tree;

	tree.mpRootNode = tree.CreateNode(nullptr, 0, 0, 0,
		800, 600, 600);

	tree.Run();

	SetStaticObj(tree);
	SetDynamicObj(tree);

	Timer timer;

	timer.Init();
	while(1)
	{
		tree.PreFrame();

		timer.Frame();
		tree.PreFrame();


		for (auto iObj : DynamicObjList) {
			iObj.second->Move(timer.mfSPF);
			
			if (tree.AddDynamicObject(iObj.second)) {
				check = true;
			}
			else
			{
				check = false;
			}
		}

		if (check)
		{
			std::cout << std::endl << "                  Collision Occurred with "
				<< "DynamicObject[" << rtn.first << "] and "
				<< "DynamicObject[" << rtn.second << "]\n";

			auto iter1 = DynamicObjList.find(rtn.first);
			if (iter1 != DynamicObjList.end()) {
				delete iter1->second;
				DynamicObjList.erase(iter1);
			}

			auto iter2 = DynamicObjList.find(rtn.second);
			if (iter2 != DynamicObjList.end()) {
				delete iter2->second;
				DynamicObjList.erase(iter2);
			}
			Sleep(4000);
			
		}
		
		tree.Render();

		
		std::cout << "Object inform!\n";
		for (auto iObj : DynamicObjList)
		{
			std::cout << "DynamicObject[" << iObj.first << "]" <<
				iObj.second->iNodeIndex << "     //   " <<
				iObj.second->mBox.v.x << ", " <<
				iObj.second->mBox.v.y << ", " <<
				iObj.second->mBox.v.z <<
				std::endl;
		}

		timer.Render();

		Sleep(10);
	}
	timer.Release();


	for (auto list : StaticObjList) {
		delete list.second;
	}
	StaticObjList.clear();
	for (auto list : DynamicObjList) {
		delete list.second;
	}
	DynamicObjList.clear();

	tree.Release();
}
