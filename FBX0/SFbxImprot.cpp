#include "SFbxImprot.h"

bool SFbxImprot::Load(W_STR filename)
{
	C_STR name = wtm(filename);
	bool ret = m_pFbxImporter->Initialize(name.c_str());
	ret = 
	return true
}

void SFbxImprot::PreProcess(FbxNode* fbxNode)
{
	if (fbxNode == nullptr) return; // if parameter is nullptr then return
	C_STR name = fbxNode->GetName();  // get name from fbxNode
	FbxMesh* fbxMesh = fbxNode->GetMesh(); // get mesh from fbxNode
	if (fbxMesh != nullptr)
	{
		m_pNodeList.push_back(fbxNode); // if Mesh is not nullptr, pushback fbxNode. 매시가 존재하는 노드라면 리스트에 넣겠다.
	}
	UINT iNumChild = fbxNode->GetChildCount(); // 자식노드 얻어서
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		FbxNode* pChildNode = fbxNode->GetChild(iChild); // 반복문으로 자식노드 수 만큼 순회
		PreProcess(pChildNode); // 재귀함수 호출
	}
}

void SFbxImprot::LoadMesh(FbxNode* node)
{

}

bool SFbxImprot::Init()
{
	return false;
}

bool SFbxImprot::Release()
{
	return false;
}
