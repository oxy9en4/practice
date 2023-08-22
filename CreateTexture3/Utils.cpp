#include "Utils.h"


bool Rect::operator == (Rect& p)
{
    if (fabs(v.x - p.v.x) > 0.0001f)
    {
        if (fabs(v.y - p.v.y) > 0.0001f)
        {
            if (fabs(m_fWidth - p.m_fWidth) > 0.0001f)
            {
                if (fabs(m_fHeight - p.m_fHeight) > 0.0001f)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Rect::operator != (Rect& p)
{
    return !(*this == p);
}
Rect Rect::operator + (Rect& p)
{
    Rect rt;
    float fMinX = min(m_Min.x, p.m_Min.x);
    float fMinY = min(m_Min.y, p.m_Min.y);
    float fMaxX = max(m_Max.x, p.m_Max.x);
    float fMaxY = max(m_Max.y, p.m_Max.y);
    Vector2 center = { (fMinX + fMaxX) * 0.5f, (fMinY + fMaxY) * 0.5f };
    rt.Set(center, fMaxX - fMinX, fMaxY - fMinY);
    return rt;
}
Rect Rect::operator - (Rect& p)
{
    Rect rt;
    rt.mbEnable = false;
    if (ToRect(p))
    {
        //left, top          right
        //      bottom
        float fx = (m_Min.x > p.m_Min.x) ? m_Min.x : p.m_Min.x;
        float fy = (m_Min.y > p.m_Min.y) ? m_Min.y : p.m_Min.y;
        float right = (m_Max.x < p.m_Max.x) ? m_Max.x : p.m_Max.x;
        float bottom = (m_Max.y < p.m_Max.y) ? m_Max.y : p.m_Max.y;
        Vector2 center = { (fx + right) * 0.5f, (fy + bottom) * 0.5f };
        rt.Set(center, right - fx, bottom - fy);
        rt.mbEnable = true;
    }
    return rt;
}
Rect Rect::operator - (Vector2& p)
{
    v.x -= p.x;
    v.y -= p.y;
    return Rect(v.x, v.y, m_fWidth, m_fHeight);
}
Rect Rect::operator * (float fValue)
{
    if (fValue <= 0.0f)
    {
        return *this;
    }
    m_fWidth *= fValue;
    m_fHeight *= fValue;
    return Rect(v.x, v.y, m_fWidth, m_fHeight);
}
Rect Rect::operator / (float fValue)
{
    if (fValue <= 0.0f)
    {
        return *this;
    }
    m_fWidth /= fValue;
    m_fHeight /= fValue;
    return Rect(v.x, v.y, m_fWidth, m_fHeight);
}
void Rect::Set(Vector2 p)
{
    m_Center = p;
    v = { p.x, p.y };
    s = { m_fWidth, m_fHeight };
    Set(m_fWidth, m_fHeight);
}
void Rect::Set(float fw, float fh)
{
    m_fWidth = fw;
    m_fHeight = fh;
    m_Half = { m_fWidth * 0.5f,m_fHeight * 0.5f };
    m_Point[0] = { v.x, v.y };
    m_Point[1] = { v.x + m_fWidth, v.y };
    m_Point[2] = { v.x + m_fWidth, v.y - m_fHeight };
    m_Point[3] = { v.x, v.y - m_fHeight };
    m_Max = m_Point[1];
    m_Min = m_Point[3];
}
void Rect::Set(Vector2 p, float fw, float fh)
{
    m_Center = p;
    v = { p.x - fw / 2.0f, p.y + fh / 2.0f };
    s = { fw, fh };
    Set(fw, fh);
}
void Rect::Set(float fx, float fy, float fw, float fh)
{
    m_Center.x = fx;
    m_Center.y = fy;
    s = { fw, fh };
    v = { fx - fw / 2.0f, fy + fh / 2.0f };

    Set(fw, fh);
}

bool Rect::ToRect(Rect& rt)
{
    Rect sum = (*this) + rt;
    float fX = m_fWidth + rt.m_fWidth;
    float fY = m_fHeight + rt.m_fHeight;
    if (sum.m_fWidth <= fX)
    {
        if (sum.m_fHeight <= fY)
        {
            return true;
        }
    }
    return false;
}
bool Rect::ToPoint(Vector2& p)
{
    if (m_Min.x <= p.x && m_Max.x >= p.x &&
        m_Min.y <= p.y && m_Max.y >= p.y)
    {
        return true;
    }
    return false;
}
Rect::Rect() : mbEnable(true) {}

Rect::Rect(float fx, float fy, float fw, float fh)
{
    mbEnable = true;
    Set(fx, fy, fw, fh);
}



bool Box::operator ==(Box& p)
{
	if (fabs(v.x - p.v.x) < EPSILON
		&& fabs(v.y - p.v.y) < EPSILON
		&& fabs(v.z - p.v.z) < EPSILON
		&& fabs(size.x - p.size.x) < EPSILON
		&& fabs(size.y - p.size.y) < EPSILON
		&& fabs(size.z - p.size.z) < EPSILON)
	{
		return true;
	}
	return false;
}

bool Box::operator !=(Box& p) {
	return !(*this == p);
}

Box Box::operator +(Box& p) {
	Box tmp;
	float fMinX = min(mMin.x, p.mMin.x);
	float fMinY = min(mMin.y, p.mMin.y);
	float fMinZ = min(mMin.z, p.mMin.z);
	float fMaxX = max(mMax.x, p.mMax.x);
	float fMaxY = max(mMax.y, p.mMax.y);
	float fMaxZ = max(mMax.z, p.mMax.z);
	Vector3 pivot = { fMinX, fMinY, fMinZ };
	tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
	return tmp;
}

Box Box::operator -(Box& p) {
	Box tmp;
	tmp.mbEnable = false;

	if (ToBox(p)) {

		float fMinX = max(mMin.x, p.mMin.x);
		float fMinY = max(mMin.y, p.mMin.y);
		float fMinZ = max(mMin.z, p.mMin.z);

		float fMaxX = min(mMax.x, p.mMax.x);
		float fMaxY = min(mMax.y, p.mMax.y);
		float fMaxZ = min(mMax.z, p.mMax.z);

		Vector3 pivot(fMinX, fMinY, fMinZ);
		tmp.Set(pivot, fMaxX - fMinX, fMaxY - fMinY, fMaxZ - fMinZ);
		tmp.mbEnable = true;
	}
	return tmp;
}
Box Box::operator -(Vector3& p) {
	return Box(v.x - p.x, v.y - p.y, v.z - p.z, size.x, size.y, size.z);
}
Box Box::operator *(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x * f, v.y * f, v.z * f, size.x, size.y, size.z);
}
Box Box::operator /(float f) {
	if (f <= EPSILON) return *this;
	return Box(v.x / f, v.y / f, v.z / f, size.x, size.y, size.z);
}


void Box::Set(float fw, float fh, float fd) {
	size.x = fw;
	size.y = fh;
	size.z = fd;
	mHalf = { fw * 0.5f, fh * 0.5f, fd * 0.5f };
	mPoint[0] = { v.x, v.y, v.z };
	mPoint[1] = { v.x + fw, v.y, v.z };
	mPoint[2] = { v.x + fw, v.y + fh, v.z };
	mPoint[3] = { v.x, v.y + fh, v.z };

	mPoint[4] = { v.x, v.y, v.z + fd };
	mPoint[5] = { v.x + fw, v.y, v.z + fd };
	mPoint[6] = { v.x + fw, v.y + fh, v.z + fd };
	mPoint[7] = { v.x, v.y + fh, v.z + fd };

	mMin = mPoint[0];
	mMax = mPoint[6];
	mCenter = (mMin + mMax) * 0.5f;
}

void Box::Set(float fx, float fy, float fz, float fw, float fh, float fd) {
	v = { fx, fy, fz };

	Set(fw, fh, fd);
}

void Box::Set(Vector3 p, float fw, float fh, float fd) {
	v = { p.x, p.y, p.z };
	Set(fw, fh, fd);
}

void Box::Set(Vector3 p, Vector3 o)
{
	v = { p.x, p.y, p.z };
	Set(o.x, o.y, o.z);
}


bool Box::ToBox(Box& p) {
	Box sum = (*this) + p; // 제대로 더해지는지 확인
	float fX = size.x + p.size.x;
	float fY = size.y + p.size.y;
	float fZ = size.z + p.size.z;
	if (sum.size.x - fX <= EPSILON
		&& sum.size.y - fY <= EPSILON
		&& sum.size.z - fZ <= EPSILON)
	{
		return true;
	}
	return false;
}


bool Box::BoxToBox(Box& p, Box& t) {
	Box sum = p + t;

	if (sum.v.x - (p.size.x + t.size.x) > EPSILON) return false;
	if (sum.v.y - (p.size.y + t.size.y) > EPSILON) return false;
	if (sum.v.z - (p.size.z + t.size.z) > EPSILON) return false;
	return true;
}