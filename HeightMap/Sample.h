#pragma once
#include "Core.h"
#include "PlaneObj.h"
#include "HeightMap.h"

using std::shared_ptr;
using std::make_shared;
class Sample : public Core
{
	HeightMap* _map;
public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	void DebugMode();
};

