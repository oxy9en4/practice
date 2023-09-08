#pragma once
#include "SpriteObj.h"
#include "bullet.h"

using sBullet = std::unique_ptr<bullet>;

enum CharState
{
	CHAR_DEATH = -1,
	CHAR_IDLE = 0,
	CHAR_ATTACK = 1,
	CHAR_DODGE = 2,
	CHAR_CANCLE = 3,
};



class mainchar : public SpriteUV
{
public:
	int m_State = 0;
	std::vector<UVRect>	m_IdleList;
	std::vector<UVRect>	m_AttackList;
	std::vector<UVRect>	m_DodgeList;
	std::vector<UVRect>	m_DeathList;

	
	sBullet  Bullet = nullptr;
	void  SetUVFrame(int iNumRow, int iNumColumn) override;

	bool Init() override;
	bool Frame() override;
	bool Render() override;
};

