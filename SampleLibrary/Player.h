#pragma once
#include "stdafx.h"
#include "PlaneObj.h"
#include "Input.h"

class Player : public PlaneObj
{
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();
};

