#pragma once
#include "Utils.h"

enum class CollisionTypeA
{
	CT_NONE,
	CT_OVERLAB,
	CT_STAY,
	CT_EXIT,
};

enum CollisiontTypeB
{
	A_OUTSIDE = 0,
	A_SPANNING = 1,
	A_DestBig,
	A_SrcBig,
};

enum CollisionType
{
	CT_OUTSIDE = 0,
	CT_SPANNING = 1,
	//CT_INSIDE
	CT_DestBig,
	CT_SrcBig,
	//CT_FRONT,
	//CT_BACK,
	//CT_ONPLANE,
};

class Collision
{
public:
	static bool RectToRect(Rect& rt1, Rect& rt2)
	{
		Rect sum = rt1 + rt2;
		float fX = rt1.m_fWidth + rt2.m_fWidth;
		float fY = rt1.m_fHeight + rt2.m_fHeight;
		if (fabs(sum.m_fWidth - fX) < EPSILON)
		{
			if (fabs(sum.m_fHeight - fY < EPSILON))
			{
				return true;
			}
		}
		return false;
	}
	static bool RectToPoint(Rect& rt, Vector2& p)
	{
		if (rt.m_Min.x <= p.x && rt.m_Max.x >= p.x
			&&
			rt.m_Min.y <= p.y && rt.m_Max.y >= p.y)
		{
			return true;
		}
		return false;
	}
	static CollisionType BoxToBox(Box& box1, Box& box2)
	{
		CollisionType ret = CT_OUTSIDE;
		Vector3 dir = box1.mCenter - box2.mCenter;
		if (BoxInBox(box1, box2))
		{
			ret = CT_DestBig;
			return ret;
		}
		if (BoxInBox(box2, box1))
		{
			ret = CT_SrcBig;
			return ret;
		}
		if (dir.x <= (box1.mHalf.x + box2.mHalf.x))
		{
			if (dir.y <= (box1.mHalf.y + box2.mHalf.y))
			{
				if (dir.z <= (box1.mHalf.z + box2.mHalf.z))
				{
					ret = CT_SPANNING;
				}
			}
		}
		return ret;
	}
	static bool BoxInBox(Box& rt1, Box& rt2)
	{
		if (rt1.mMin.x <= rt2.mMin.x && rt1.mMax.x >= rt2.mMax.x)
		{
			if (rt1.mMin.y <= rt2.mMin.y && rt1.mMax.y >= rt2.mMax.y)
			{
				if (rt1.mMin.z <= rt2.mMin.z && rt1.mMax.z >= rt2.mMax.z)
				{
					return true;
				}
			}
		}
		return false;
	}
	static bool BoxToPoint(Box& rt, Vector3& p)
	{
		if (rt.mMin.x <= p.x && rt.mMax.x >= p.x
			&&
			rt.mMin.y <= p.y && rt.mMax.y >= p.y
			&&
			rt.mMin.z <= p.z && rt.mMax.z >= p.z)
		{
			return true;
		}
		return false;
	}
	static bool SphereToPoint(Sphere& s, Vector3 v)
	{
		Vector3 d = v - s.vCenter;
		float fDistance = d.Length();
		if (fDistance <= s.fRadius)
		{
			return true;
		}
		return false;
	}
	static bool CircleToPoint(Circle& s, Vector2 v)
	{
		Vector2 d = v - s.vCenter;
		float fDistance = d.Length();
		if (fDistance <= s.fRadius)
		{
			return true;
		}
		return false;
	}
	static bool SphereToSphere(Sphere& s1, Sphere& s2)
	{
		Vector3 d = s1.vCenter - s2.vCenter;
		float fDistance = d.Length();
		if (fDistance <= (s1.fRadius + s2.fRadius))
		{
			return true;
		}
		return false;
	}
	static bool CircleToCircle(Circle& s1, Circle& s2)
	{
		Vector2 d = s1.vCenter - s2.vCenter;
		float fDistance = d.Length();
		if (fDistance <= (s1.fRadius + s2.fRadius))
		{
			return true;
		}
		return false;
	}
};