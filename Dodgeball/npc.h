#pragma once
#include "mainchar.h"
#include <cstdlib>
#include <ctime>

class npc : public mainchar {
public:
    npc();

    bool Init() override;
    bool Frame() override;
    bool Render() override;

private:
    void DecideAction(); // 확률에 따라 행동을 결정하는 함수

    // 행동 확률 (0.0 ~ 1.0)
    float moveProbability = 0.1f;   // 이동 확률
    float dodgeProbability = 0.4f;  // 회피 확률
    float attackProbability = 0.5f; // 공격 확률
    // 이동 관련 변수
    bool isMoving = false;
    Vector3 moveTarget;

    // 회피 관련 변수
    bool isDodging = false;

    // 공격 관련 변수
    bool isAttacking = false;
    float attackCooldown = 0.0f;
};
