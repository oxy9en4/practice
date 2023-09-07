#include "npc.h"

extern Vector3 posPlayer;

npc::npc() {
    // 난수 초기화
    srand(static_cast<unsigned int>(time(nullptr)));

    // npc 초기 설정
    moveProbability = 0.1f;     // 이동 확률
    dodgeProbability = 0.1f;    // 회피 확률
    attackProbability = 0.5f;   // 공격 확률
    isMoving = false;
    isDodging = false;
    isAttacking = false;
    attackCooldown = 0.0f;
}

bool npc::Init() {
    mainchar::Init();

    return true;
}

bool npc::Frame() {

    if (!isMoving && !isDodging && !isAttacking) {
        DecideAction();
    }

    // 이동 처리
    if (isMoving || isDodging) {

        float moveSpeed = 150.0f; // 초당 이동 속도 (픽셀/초)
        float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;
        if (m_State == CHAR_DODGE) maxMoveDistanceThisFrame *= 1.5f;
        if ((moveTarget - m_vPos).Length() > 1.0f) {
            // 목표 위치까지 최대 이동 거리만큼 이동
            Vector3 moveDirection = (moveTarget - m_vPos).NormVector();
            m_vPos += moveDirection * maxMoveDistanceThisFrame;
        }
        else {
            // 목표 위치에 도착한 경우, 위치를 목표 위치로 설정
            m_vPos = moveTarget;
            isMoving = false;
        }
    }

    PlaneObj::Frame();
    m_fElapsedTimer += g_fSPF;
    if (m_fElapsedTimer >= m_fOffsetTime && m_State < CHAR_CANCLE) // cancle 상태가 아니라면 index 증가
    {
        m_iCurrentAnimIndex++;
        m_fElapsedTimer -= m_fOffsetTime;
    }
    else if (m_fElapsedTimer >= m_fOffsetTime && m_State == CHAR_CANCLE) // cancle 상태라면 역재생
    {
        m_iCurrentAnimIndex--;
        m_fElapsedTimer -= m_fOffsetTime;
    }
    // 회피 처리
    if (isDodging) {
        if (m_iCurrentAnimIndex >= m_DodgeList.size() - 1)
        {
            isDodging = false; // 회피 동작이 끝나면 플래그를 false로 설정
        }
    }

    // 공격 처리
    if (isAttacking) {
        Bullet->m_vPos = m_vPos;
        Bullet->UpdateDir(posPlayer);
        Bullet->mTarget = Bullet->m_vPos;

        UpdateDir(posPlayer);
        mTarget = m_vPos;

        // 공격 쿨다운 감소
        if (attackCooldown > 0.0f) {
            attackCooldown -= g_fSPF;
        }
        
    }

    if (Bullet->visible) Bullet->Frame();

    return true;
}

bool npc::Render() {
    UVRect uv;
    switch (m_State)
    {
    case CHAR_IDLE:
        if (m_iCurrentAnimIndex >= m_IdleList.size())
        {
            m_iCurrentAnimIndex = 0;
        }
        uv = m_IdleList[m_iCurrentAnimIndex];
        break;
    case CHAR_ATTACK:
        if (m_iCurrentAnimIndex >= m_AttackList.size())
        {
            m_iCurrentAnimIndex = m_AttackList.size() - 1;
            m_State = CHAR_CANCLE;

            Bullet->m_iCurrentAnimIndex = 0;
            Bullet->visible = true;
            isAttacking = false; // 공격 동작이 끝나면 플래그를 false로 설정
            attackCooldown = 2.0f; // 공격 쿨다운 설정 (예: 2초)
        }
        uv = m_AttackList[m_iCurrentAnimIndex];
        break;
    case CHAR_DODGE:
        if (m_iCurrentAnimIndex >= m_DodgeList.size())
        {
            m_iCurrentAnimIndex = 0;
            m_State = CHAR_IDLE;
        }
        uv = m_DodgeList[m_iCurrentAnimIndex];
        break;
    case CHAR_CANCLE:
        if (m_iCurrentAnimIndex == 0)
        {
            m_State = CHAR_IDLE;
        }
        uv = m_AttackList[m_iCurrentAnimIndex];
        break;
    }
    m_VertexList[0].t = uv.m_Min;
    m_VertexList[1].t.x = uv.m_Max.x;
    m_VertexList[1].t.y = uv.m_Min.y;

    m_VertexList[2].t.x = uv.m_Min.x;
    m_VertexList[2].t.y = uv.m_Max.y;
    m_VertexList[3].t = m_VertexList[2].t;

    m_VertexList[4].t = m_VertexList[1].t;
    m_VertexList[5].t = uv.m_Max;

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);

    PreRender();
    PostRender();

    Bullet->Render();
    return true;
}

void npc::DecideAction() {
    // 무작위 확률을 생성합니다.
    float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    // 확률에 따라 행동을 선택합니다.
    if (randomValue < moveProbability) {
        m_State = CHAR_IDLE; // 일단 이동하지 않고 멈춰서 기다립니다.
        isMoving = true; // 이동 플래그를 true로 설정
        float targetX = static_cast<float>(rand() % 800 - 400); // -400에서 400 사이의 랜덤한 위치로 이동
        float targetY = static_cast<float>(rand() % 600 - 300); // -300에서 300 사이의 랜덤한 위치로 이동
        moveTarget = Vector3(targetX, targetY, 0.0f);
        UpdateDir(moveTarget);
        mTarget = moveTarget;
        m_State = 0;
        m_iCurrentAnimIndex = 0;
    }
    else if (randomValue < (moveProbability + dodgeProbability)) {
        float targetX = static_cast<float>(rand() % 800 - 400); // -400에서 400 사이의 랜덤한 위치로 이동
        float targetY = static_cast<float>(rand() % 600 - 300); // -300에서 300 사이의 랜덤한 위치로 이동
        moveTarget = Vector3(targetX, targetY, 0.0f);
        UpdateDir(moveTarget);
        m_State = CHAR_DODGE; // 회피 상태로 설정
        m_iCurrentAnimIndex = 0;
        isDodging = true; // 회피 플래그를 true로 설정
    }
    else {
        if (Bullet->visible == false) {
            m_State = CHAR_ATTACK; // 공격 상태로 설정
            Bullet->m_vPos = posPlayer;
            Bullet->UpdateDir(posPlayer);
            Bullet->mTarget = Bullet->m_vPos;

            UpdateDir(posPlayer);
            mTarget = posPlayer;
            m_iCurrentAnimIndex = 0;
            isAttacking = true; // 공격 플래그를 true로 설정
        }
        else {
            m_State = CHAR_IDLE; // 아직 공격 쿨다운 중이면 대기 상태로 설정
        }
    }
}
