#include "stdafx.h"
#include "Octree.h"
#include "Timer.h"


// Static Object 정적 오브젝트를 생성하고 리스트에 추가하는 함수
void SetStaticObj(Octree& tree)
{
	if (tree.mpRootNode == nullptr) return; // mpRootNode는 공간 그 자체. 
						//공간에 대한 정보도 담고 있기 때문에 RootNode가 null이라면 함수를 실행시키지 않겠다는 뜻
	
	int iMaxWidth = tree.mpRootNode->mBox.size.x;   // size.x y z는 너비 높이 깊이를 나타낸다.
	int iMaxHeight = tree.mpRootNode->mBox.size.y;
	int iMaxDepth = tree.mpRootNode->mBox.size.z;

	for (int i = 0; i < 10; ++i) {
		Object* obj = new StaticObject(); // Object를 상속받은 StaticObject를 동적 할당한다. 이 때, obj의 포인터로 부모인 Object를 사용 가능.
		obj->wsName = L"StaticObj"; // 이름
		obj->wsName += std::to_wstring(i); // 번호(인덱스)
		obj->mBox.v = { (float)(rand() % iMaxWidth), // rand()는 난수 생성기(무작위 수 생성)
						(float)(rand() % iMaxHeight), // 이것을 iMax어쩌구(너비, 높이, 깊이)로 %(나머지 계산)을 해 주면
						(float)(rand() % iMaxDepth) }; // 최대 iMaxWidth, Height, Depth 값 안에서 난수를 생성하게 된다.
		obj->SetBox(obj->mBox.v,						//SetBox로 obj의 위치정보(position 혹은 pivot)인 v
					(float)((rand() % 10) + 100.0f),	//그리고 크기는 0~10 까지의 난수에 100을 더한다.
					(float)((rand() % 10) + 100.0f),	//그러니까 100~110까지의 랜덤한 가로 세로 높이를 지니게 되는 것
					(float)((rand() % 10) + 100.0f));	//부피를 정해주는 코드
		tree.AddStaticObject(obj);						// obj의 위치와 부피를 토대로 어떤 노드에 '완전히' 포함되는지 찾아서 해당 노드의
														// mStaticObjectList에 보관(이 List는 공간 노드가 자기 공간 안에 어떤 오브젝트들이
														// 존재하는지를 파악하는데 사용

		obj->iListIndex = i;							//  오브젝트의 인덱스(번호)를 부여해줌
		StaticObjList.insert(std::make_pair(i, obj));	// 정적오브젝트(Static Object)를 보관하는 List에 obj를 insert한다.
														// StaticObjList는 map 컨테이너로 되어 있고, map은
														// key와 value 쌍을 저장한다. 그렇기 때문에 pair로 key(i)와 value(obj)를 전달.
		
	}
}

//동적 오브젝트를 생성하고 리스트에 추가하는 함수, 정적 오브젝트와 거의 유사함.
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
		Vector3 target = { (float)randstep(0, iMaxWidth),		// 정적 오브젝트에는 없었던 target이라는 변수
							(float)randstep(0, iMaxHeight),		// 동적 오브젝트는 이름 그대로 목적지를 향해 매 프레임마다 이동함
							(float)randstep(0, iMaxDepth) };	// 따라서 목적지를 랜덤하게 부여해줌. randstep은 stdafx에 정의되어있는데
																// 위의 "rand() % 최대값" 형태와 비슷하게
																// randstep(0, 100)이라고 하면 0부터 100까지 사이에서 난수를 생성함
		
		obj->SetTarget(target);									// 동적 obj의 target을 설정해주는 setter 함수
		if (!tree.AddDynamicObject(obj))						// AddDynamicObject는 참거짓을 반환하는 bool 타입의 함수
		{
			obj->iListIndex = i;								// obj의 번호를 부여(인덱스)
			DynamicObjList.insert(std::make_pair(i, obj));		// 정적오브젝트와 이하동문
		}
		
	}
}


int main()
{
	bool check = false;										// check는 오브젝트가 이동한 후 충돌이 있었는지를 확인하는 bool 타입 변수
	std::cout.precision(3);									// precision(3)은 내가 출력하는 모든 수를 3자리로 출력하겠다는 뜻. 보통은 6자리임.
															// (332.445)로 출력될 수를 332로 반올림하여 표현해줌.
	Octree tree;											// 옥트리 생성. 이름은 tree

	tree.mpRootNode = tree.CreateNode(nullptr, 0, 0, 0,		// mpRootNode는 공간의 최상위 노드. 공간 전체를 이야기함.
		800, 600, 600);										// 화면좌표계로 좌상단(0,0,0)부터 너비, 높이, 깊이가 각각 800 600 600으로 설정.

	tree.Run();												// Run() 함수는 tree를 만드는 BuildTree를 호출.

	SetStaticObj(tree);										// main 함수 바로 위에서 정의한 SetStaticObj를 호출
	SetDynamicObj(tree);

	Timer timer;											// timer 생성

	timer.Init();											// timer 초기화
	while(1)												// while (조건문) 조건문 안쪽이 1(true)이기 때문에 별도의 탈출문이 없으니 무한히 반복
	{
		tree.PreFrame();									// 밥을 먹는 것을 Frame이라고 한다면 밥 먹기 전에 손을 씻는 것이 순서.
															// 이 때 손을 씻는 작업을 PreFrame이라고 함

		timer.Frame();
		tree.PreFrame();									// 밥을 먹은 후 양치를 한다면, 이것이 PreFrame. Frame 이후에 해야 할 작업들.


		for (auto iObj : DynamicObjList) {					// auto(자동으로 데이터 타입을 컴파일러가 유추함) DynamicObjList의 원소들을 "순회"
															// DynamicObjList는 map이고, pair(int, Object*)를 저장하고 있음
			iObj.second->Move(timer.mfSPF);					// 따라서 pair의 두번째(second) 원소인 Object에 접근하여 그 것의 Move함수를 호출
															// mfSPF는 timer의 member인 float형 Second Per Frame을 나타냄
															// Second Per Frame은 한 프레임 당 걸린 시간을 의미
			if (tree.AddDynamicObject(iObj.second)) {		// 움직인 후 충돌이 있는지 검사. 충돌했다면 check는 true
				check = true;
			}
			else
			{
				check = false;
			}
		}

		if (check)											// move 시 충돌이 일어났다면
		{
			if (DToD)										// 그리고 그것이 DToD. Dynamic To Dynamic이었다면(동적 오브젝트 끼리라면)
			{
				std::cout << std::endl << "                  Collision Occurred with "	// 충돌이 일어났음을 텍스트로 출력
					<< "DynamicObject[" << rtn.first << "] and "						// rtn은 move함수에서 충돌이 일어난 오브젝트 둘을 보관
					<< "DynamicObject[" << rtn.second << "]\n";							

				auto iter1 = DynamicObjList.find(rtn.first);// DynamicObjList는 pair(int, Object*)이며 find는 value를 통해 key를 찾아내는 함수
				if (iter1 != DynamicObjList.end()) {		// 만약 value에 맞는 key가 없다면 iter1는 map의 end를 가리키게 되어있음
					delete iter1->second;					// 따라서 map.end()와 같다면 그것은 find로 찾지 못했다는 것을 의미.
					DynamicObjList.erase(iter1);			// end()와 다르다면 찾았다는 것이기 때문에 obj를 리스트에서 제거
				}

				auto iter2 = DynamicObjList.find(rtn.second);
				if (iter2 != DynamicObjList.end()) {
					delete iter2->second;
					DynamicObjList.erase(iter2);
				}
				Sleep(10000);								// 10초(10,000ms 밀리세컨드) 동안 멈춤.
			}
			else {											// DtD가 아니라면( Static To Dynamic 이라면) Static과 Dynamic 간 충돌
				std::cout << std::endl << "                  Collision Occurred with "
					<< "StaticObject[" << rtn.first << "] and "
					<< "DynamicObject[" << rtn.second << "]\n";

				auto iter1 = StaticObjList.find(rtn.first);
				if (iter1 != StaticObjList.end()) {
					delete iter1->second;
					StaticObjList.erase(iter1);
				}

				auto iter2 = StaticObjList.find(rtn.second);
				if (iter2 != StaticObjList.end()) {
					delete iter2->second;
					StaticObjList.erase(iter2);
				}
				Sleep(10000);
			}
		}
		
		tree.Render();													//Render는 화면에 출력하는 함수이지만, 현재 비어있음

		
		std::cout << "Object inform!\n";								//오브젝트 정보 출력
		for (auto iObj : StaticObjList)									// Static Object List를 순회하며 모든 오브젝트를 출력
		{
			std::cout << "StaticObject[" << iObj.first << "]" <<
				iObj.second->iNodeIndex << "      (" <<
				iObj.second->mBox.v.x << ", " <<
				iObj.second->mBox.v.y << ", " <<
				iObj.second->mBox.v.z << ")\n";
		}
		for (auto iObj : DynamicObjList)
		{
			std::cout << "DynamicObject[" << iObj.first << "]" <<		// Dynamic Object List를 순회하며 모든 오브젝트를 출력
				iObj.second->iNodeIndex << "       (" <<
				iObj.second->mBox.v.x << ", " <<
				iObj.second->mBox.v.y << ", " <<
				iObj.second->mBox.v.z << ")\n";
		}

		timer.Render();

		Sleep(10);
	}
	timer.Release();


	for (auto list : StaticObjList) {								// 프로그램 종료 시 List를 순회하며 동적 할당했던 Object들을 제거
		delete list.second;											// 그렇지 않으면 메모리 누수가 발생(memory leak)
	}
	StaticObjList.clear();
	for (auto list : DynamicObjList) {
		delete list.second;
	}
	DynamicObjList.clear();

	tree.Release();
}
