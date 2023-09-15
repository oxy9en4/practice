#include "SMap.h"

float SMap::GetHeightOfVertex(UINT iVertexIndex)
{

    return 0.0f;
}

Vector3 SMap::GetNormalOfVertex(UINT iVertexIndex)
{
    return Vector3(0, 1, 0);
}

Vector4 SMap::GetColorOfVertex(UINT iVertexIndex)
{
    return Vector4(1, 1, 1, 1);
}

Vector2 SMap::GetTextureOfVertex(UINT row, UINT col)
{
    return Vector2( (float)col / (float)(m_iNumCols - 1),     // 
                    (float)row / (float)(m_iNumRows - 1) );   //
}

bool SMap::CreateVertexData()
{
    if (m_VertexList.size() > 0)
    {
        m_VertexList.clear();
    }
    UINT rSize = m_iNumCols * m_iNumRows;
    m_VertexList.resize(rSize);

    float fHalfCols = (m_iNumCols - 1) * 0.5f;
    float fHalfRows = (m_iNumRows - 1) * 0.5f;

    m_iNumCellRows = (m_iNumRows - 1);
    m_iNumCellCols = (m_iNumCols - 1);

    m_iNumFace = m_iNumCellRows * m_iNumCellCols * 2;

    float tx0ffsetU = 1.0f / m_iNumCellCols;
    float txOffsetV = 1.0f / m_iNumCellRows;

    for (int iRow = 0; iRow < m_iNumRows; iRow++)
    {
        for (int iCol = 0; iCol < m_iNumCols; iCol++)
        {
            int  iVertexIndex = iRow * m_iNumCols + iCol;
            m_VertexList[iVertexIndex].p.x = (iCol - fHalfCols) * 1.0f;
            m_VertexList[iVertexIndex].p.z = -((iRow - fHalfRows) * 1.0f);
            m_VertexList[iVertexIndex].p.y = GetHeightOfVertex(iVertexIndex);
            m_VertexList[iVertexIndex].n = GetNormalOfVertex(iVertexIndex);
            m_VertexList[iVertexIndex].c = GetColorOfVertex(iVertexIndex);
            m_VertexList[iVertexIndex].t = GetTextureOfVertex(iRow, iCol);
        }
    }

    return true;
}

bool SMap::CreateIndexData()
{
    m_IndexList.resize(m_iNumFace * 3);

    int iCurIndex = 0;
    for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
    {
        for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
        {
            //0	1    4   
            //2	   3 5
            int iNextRow = iRow + 1;
            int iNextCol = iCol + 1;
            m_IndexList[iCurIndex + 0] = iRow * m_iNumCols + iCol;
            m_IndexList[iCurIndex + 1] = iRow * m_iNumCols + iNextCol;
            m_IndexList[iCurIndex + 2] = iNextRow * m_iNumCols + iCol;
            m_IndexList[iCurIndex + 3] = m_IndexList[iCurIndex + 2];
            m_IndexList[iCurIndex + 4] = m_IndexList[iCurIndex + 1];
            m_IndexList[iCurIndex + 5] = iNextRow * m_iNumCols + iNextCol;

            iCurIndex += 6;
        }
    }
    return true;
}

bool SMap::Load(SMapDesc desc)
{
    m_MapInfo = desc;
    Object::Create(desc.strTextureFileName, desc.strShaderFileName);
    return true;
}
