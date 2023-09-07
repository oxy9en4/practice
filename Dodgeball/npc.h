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
    void DecideAction(); // Ȯ���� ���� �ൿ�� �����ϴ� �Լ�

    // �ൿ Ȯ�� (0.0 ~ 1.0)
    float moveProbability = 0.1f;   // �̵� Ȯ��
    float dodgeProbability = 0.4f;  // ȸ�� Ȯ��
    float attackProbability = 0.5f; // ���� Ȯ��
    // �̵� ���� ����
    bool isMoving = false;
    Vector3 moveTarget;

    // ȸ�� ���� ����
    bool isDodging = false;

    // ���� ���� ����
    bool isAttacking = false;
    float attackCooldown = 0.0f;
};
