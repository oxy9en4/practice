#pragma once
#include "SpriteObj.h"

enum CharState
{
	CHAR_IDLE = 0,
	CHAR_ATTACK = 1,
	CHAR_DODGE = 2,
	CHAR_CANCLE = 3,
};



class mainchar : public SpriteUV
{
public:
	UINT m_State = 0;
	std::vector<UVRect>	m_IdleList;
	std::vector<UVRect>	m_AttackList;
	std::vector<UVRect>	m_DodgeList;
	void  SetUVFrame(int iNumRow, int iNumColumn) override;

	bool Frame() override;
	bool Render() override;
};

