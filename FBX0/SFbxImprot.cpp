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
		m_pNodeList.push_back(fbxNode); // if Mesh is not nullptr, pushback fbxNode. �Žð� �����ϴ� ����� ����Ʈ�� �ְڴ�.
	}
	UINT iNumChild = fbxNode->GetChildCount(); // �ڽĳ�� ��
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		FbxNode* pChildNode = fbxNode->GetChild(iChild); // �ݺ������� �ڽĳ�� �� ��ŭ ��ȸ
		PreProcess(pChildNode); // ����Լ� ȣ��
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
