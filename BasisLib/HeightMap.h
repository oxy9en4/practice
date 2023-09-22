#pragma once
#include "SMap.h"

class HeightMap : public SMap
{
public:
	std::vector<float> m_heightList;
	bool _isHeightLoad = false;



public:
	bool CreateHeightMap(std::wstring hPath);

public:
	float GetHeightOfVertex(UINT iVertexIndex) override;

	bool CreateHeightVertexData();
	bool CreateIndexData() override;

	bool LoadHeightMap(std::wstring texFileName, std::wstring shaderFileName);

};

