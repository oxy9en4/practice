#pragma once
#include "SpriteObj.h"

class bullet : public SpriteObj
{
public:
	bool visible = false;
	float lifeTime = 0.0f;

	std::vector<UVRect>	m_UVList;
	void  SetUVFrame(int iNumRow, int iNumColumn) override;

	bool Frame() override;
	bool Render() override;
};

