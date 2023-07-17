#pragma once
#include "sUtils.h"

class sCollision {
public:
	static bool RectToPoint(sRect& rt, sPoint& p) {
		if (rt.Min.x <= p.x && p.x <= rt.Max.x
			&&
			rt.Min.y <= p.y && p.y <= rt.Max.y)
		{
			return true;
		}
		return false;
	}
};