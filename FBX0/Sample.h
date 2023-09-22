#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "HeightMap.h"
#include "SDebugCamera.h"
#include "SQuadTree.h"

using std::shared_ptr;
using std::make_shared;

class Sample : public Core
{
	const Texture* m_pTex;
	HeightMap* _map = nullptr;
	shared_ptr<SDebugCamera> m_pDebugCamera;
	shared_ptr<SQuadTree> m_pQuadTree;

public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	void DebugMode();

public:
	bool DeleteDxResource() override;
	bool CreateDxResource() override;
};

