#pragma once
#include "sUtils.h"

class sCollision {
public:
	static bool RectToRect(sRect& rt1, sRect& rt2) {
		sRect sum = rt1 + rt2;
		if (sum.fWidth <= (rt1.fWidth + rt2.fWidth)) {
			if (sum.fHeight <= (rt1.fHeight + rt2.fHeight)) {
				return true;
			}
		}
		return false;
	}
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