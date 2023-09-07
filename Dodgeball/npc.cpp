#include "npc.h"

extern Vector3 posPlayer;

npc::npc() {
    // ���� �ʱ�ȭ
    srand(static_cast<unsigned int>(time(nullptr)));

    // npc �ʱ� ����
    moveProbability = 0.1f;     // �̵� Ȯ��
    dodgeProbability = 0.1f;    // ȸ�� Ȯ��
    attackProbability = 0.5f;   // ���� Ȯ��
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

    // �̵� ó��
    if (isMoving || isDodging) {

        float moveSpeed = 150.0f; // �ʴ� �̵� �ӵ� (�ȼ�/��)
        float maxMoveDistanceThisFrame = moveSpeed * g_fSPF;
        if (m_State == CHAR_DODGE) maxMoveDistanceThisFrame *= 1.5f;
        if ((moveTarget - m_vPos).Length() > 1.0f) {
            // ��ǥ ��ġ���� �ִ� �̵� �Ÿ���ŭ �̵�
            Vector3 moveDirection = (moveTarget - m_vPos).NormVector();
            m_vPos += moveDirection * maxMoveDistanceThisFrame;
        }
        else {
            // ��ǥ ��ġ�� ������ ���, ��ġ�� ��ǥ ��ġ�� ����
            m_vPos = moveTarget;
            isMoving = false;
        }
    }

    PlaneObj::Frame();
    m_fElapsedTimer += g_fSPF;
    if (m_fElapsedTimer >= m_fOffsetTime && m_State < CHAR_CANCLE) // cancle ���°� �ƴ϶�� index ����
    {
        m_iCurrentAnimIndex++;
        m_fElapsedTimer -= m_fOffsetTime;
    }
    else if (m_fElapsedTimer >= m_fOffsetTime && m_State == CHAR_CANCLE) // cancle ���¶�� �����
    {
        m_iCurrentAnimIndex--;
        m_fElapsedTimer -= m_fOffsetTime;
    }
    // ȸ�� ó��
    if (isDodging) {
        if (m_iCurrentAnimIndex >= m_DodgeList.size() - 1)
        {
            isDodging = false; // ȸ�� ������ ������ �÷��׸� false�� ����
        }
    }

    // ���� ó��
    if (isAttacking) {
        Bullet->m_vPos = m_vPos;
        Bullet->UpdateDir(posPlayer);
        Bullet->mTarget = Bullet->m_vPos;

        UpdateDir(posPlayer);
        mTarget = m_vPos;

        // ���� ��ٿ� ����
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
            isAttacking = false; // ���� ������ ������ �÷��׸� false�� ����
            attackCooldown = 2.0f; // ���� ��ٿ� ���� (��: 2��)
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
    // ������ Ȯ���� �����մϴ�.
    float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    // Ȯ���� ���� �ൿ�� �����մϴ�.
    if (randomValue < moveProbability) {
        m_State = CHAR_IDLE; // �ϴ� �̵����� �ʰ� ���缭 ��ٸ��ϴ�.
        isMoving = true; // �̵� �÷��׸� true�� ����
        float targetX = static_cast<float>(rand() % 800 - 400); // -400���� 400 ������ ������ ��ġ�� �̵�
        float targetY = static_cast<float>(rand() % 600 - 300); // -300���� 300 ������ ������ ��ġ�� �̵�
        moveTarget = Vector3(targetX, targetY, 0.0f);
        UpdateDir(moveTarget);
        mTarget = moveTarget;
        m_State = 0;
        m_iCurrentAnimIndex = 0;
    }
    else if (randomValue < (moveProbability + dodgeProbability)) {
        float targetX = static_cast<float>(rand() % 800 - 400); // -400���� 400 ������ ������ ��ġ�� �̵�
        float targetY = static_cast<float>(rand() % 600 - 300); // -300���� 300 ������ ������ ��ġ�� �̵�
        moveTarget = Vector3(targetX, targetY, 0.0f);
        UpdateDir(moveTarget);
        m_State = CHAR_DODGE; // ȸ�� ���·� ����
        m_iCurrentAnimIndex = 0;
        isDodging = true; // ȸ�� �÷��׸� true�� ����
    }
    else {
        if (Bullet->visible == false) {
            m_State = CHAR_ATTACK; // ���� ���·� ����
            Bullet->m_vPos = posPlayer;
            Bullet->UpdateDir(posPlayer);
            Bullet->mTarget = Bullet->m_vPos;

            UpdateDir(posPlayer);
            mTarget = posPlayer;
            m_iCurrentAnimIndex = 0;
            isAttacking = true; // ���� �÷��׸� true�� ����
        }
        else {
            m_State = CHAR_IDLE; // ���� ���� ��ٿ� ���̸� ��� ���·� ����
        }
    }
}
