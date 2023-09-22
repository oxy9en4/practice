#pragma once
#include <Object.h>
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")


class SFbxImprot
{
public:
	FbxManager* m_pSDKManager = nullptr;
	FbxImporter* m_pFbxImporter = nullptr;
	FbxScene* m_pFbxScene = nullptr;
	FbxNode* m_FbxRootNode = nullptr;
	std::vector<FbxNode*> m_pNodeList;
public:
	bool Load(W_STR filename);
	void PreProcess(FbxNode* fbxNode);
	void LoadMesh(FbxNode* node);
	bool Init();
	bool Release();
};

