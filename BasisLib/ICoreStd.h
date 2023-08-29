#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include "Camera.h"
class ICore
{
public:
	static ID3D11Device* g_pDevice;
	static ID3D11DeviceContext* g_pContext;
	static Camera* g_pMainCamera;
};
