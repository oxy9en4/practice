#include "ICoreStd.h"

ID3D11Device* ICore::g_pDevice = nullptr;
ID3D11DeviceContext* ICore::g_pContext = nullptr;
Camera* ICore::g_pMainCamera = nullptr;