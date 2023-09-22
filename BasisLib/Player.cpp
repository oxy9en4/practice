#include "Player.h"


bool Player::Init()
{
    return true;
}

bool Player::Frame()
{
    if (Input::GetInstance().m_dwKeyState['A'] > KEY_UP)
    {
        m_vPos.x -= 500.0f * g_fSPF;
    }
    if (Input::GetInstance().m_dwKeyState['D'] > KEY_UP)
    {
        m_vPos.x += 500.0f * g_fSPF;
    }
    if (Input::GetInstance().m_dwKeyState['W'] > KEY_UP)
    {
        m_vPos.y += 500.0f * g_fSPF;
    }
    if (Input::GetInstance().m_dwKeyState['S'] > KEY_UP)
    {
        m_vPos.y -= 500.0f * g_fSPF;
    }

    if (m_vPos.x < -g_fMapHalfSizeX + m_vScale.x)
        m_vPos.x = -g_fMapHalfSizeX + m_vScale.x;
    if (m_vPos.x > g_fMapHalfSizeX - m_vScale.x)
        m_vPos.x = -g_fMapHalfSizeX + m_vScale.x;
    if (m_vPos.y < -g_fMapHalfSizeY + m_vScale.y)
        m_vPos.y = -g_fMapHalfSizeY + m_vScale.y;
    if (m_vPos.y > g_fMapHalfSizeY - m_vScale.y)
        m_vPos.y = g_fMapHalfSizeY - m_vScale.y;

    Vector2 rt = { m_vPos.x, m_vPos.y }; // for collision test
    SetRect(rt, m_vScale.x * 2.0f, m_vScale.y * 2.0f);

    TBASIS_EX::TMatrix matScale, matRotation, matTranslate;
    D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
    D3DXMatrixRotationZ(&matRotation, m_vRotation.z);
    D3DXMatrixTranslation(&matTranslate, m_vPos.x, m_vPos.y, m_vPos.z);
    m_matWorld = matScale * matRotation * matTranslate;
    return true;
}

bool Player::Render()
{
    PlaneObj::Render();
    return true;
}

bool Player::Release()
{
    return true;
}
