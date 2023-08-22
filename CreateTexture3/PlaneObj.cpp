#pragma once
#include "stdafx.h"
#include "PlaneObj.h"

bool PlaneObj::CreateVertexBuffer()
{
    m_VertexList.resize(6);
    m_VertexList[0].t.x = 0.0f; m_VertexList[0].t.y = 0.0f;
    m_VertexList[1].t.x = 1.0f; m_VertexList[1].t.y = 0.0f;
    m_VertexList[2].t.x = 0.0f; m_VertexList[2].t.y = 1.0f;
    m_VertexList[3].t.x = 0.0f; m_VertexList[3].t.y = 1.0f;
    m_VertexList[4].t.x = 1.0f; m_VertexList[4].t.y = 0.0f;
    m_VertexList[5].t.x = 1.0f; m_VertexList[5].t.y = 1.0f;

    m_VertexList[0].p.x = -1.0f; m_VertexList[0].p.y = 1.0f; m_VertexList[0].p.z = 0.0f;
    m_VertexList[1].p.x = 1.0f; m_VertexList[1].p.y = 1.0f; m_VertexList[1].p.z = 0.0f;
    m_VertexList[2].p.x = -1.0f; m_VertexList[2].p.y = -1.0f; m_VertexList[2].p.z = 0.0f;
    m_VertexList[3] = m_VertexList[2];
    m_VertexList[4] = m_VertexList[1];
    m_VertexList[5].p.x = 1.0f; m_VertexList[5].p.y = -1.0f; m_VertexList[5].p.z = 0.0f;

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.ByteWidth = sizeof(PT_Vertex) * m_VertexList.size();
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initialData;
    ZeroMemory(&initialData, sizeof(initialData));
    initialData.pSysMem = &m_VertexList.at(0);

    HRESULT hr = m_pDevice->CreateBuffer(
        &desc,
        &initialData,
        &m_pVertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

bool PlaneObj::Frame()
{
    Matrix matScale, matRotate, matTranslate;
    matScale.Scale(m_vScale);
    matRotate.ZRotate(m_vRotation.z);
    matTranslate.Translate(m_vPos);
    m_matWorld = matScale * matRotate * matTranslate;
    return true;
}
