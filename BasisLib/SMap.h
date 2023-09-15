#pragma once
#include "Object.h"



#define RANDOM(n)			(rand() % (n))
#define RANDOMSCOPE(s,e)	(rand() %(e-s))+s;
#define RANDOMIZE()			srand((unsigned)time(NULL))

struct SMapDesc
{
	UINT iNumRows;
	UINT iNumCols;
	float fCellDistance;
	float fScaleHeight;
	W_STR strTextureFileName;
	W_STR strShaderFileName;
};

class SMap : public Object
{
public:
	SMapDesc m_MapInfo;
	
	UINT m_iNumVertices;
	UINT m_iNumFace;
	UINT m_iNumCellRows;
	UINT m_iNumCellCols;
	UINT m_iNumCols;
	UINT m_iNumRows;

public:
	virtual float GetHeightOfVertex(UINT iVertexIndex);
	Vector3 GetNormalOfVertex(UINT iVertexIndex);
	Vector4 GetColorOfVertex(UINT iVertexIndex);
	Vector2 GetTextureOfVertex(UINT, UINT );
public:
	bool CreateVertexData() override;
	bool CreateIndexData() override;
	bool Load(SMapDesc desc);
};

