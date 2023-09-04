#include "aMath.h"

bool Vector2::operator == (Vector2& p)
{
	if (fabs(x - p.x) > EPSILON) return false;
	if (fabs(y - p.y) > EPSILON) return false;
	return true;
}
bool Vector2::operator != (Vector2& p)
{
	return !(*this == p);
}
Vector2 Vector2::operator + (Vector2& p)
{
	return Vector2(x + p.x, y + p.y);
}
Vector2 Vector2::operator - (Vector2& p)
{
	return Vector2(x - p.x, y - p.y);
}
Vector2 Vector2::operator * (float fValue)
{
	return Vector2(x * fValue, y * fValue);
}
Vector2 Vector2::operator / (float fValue)
{
	return Vector2(x / fValue, y / fValue);
}
Vector2& Vector2::operator /= (float fValue)
{
	x = x / fValue;
	y = y / fValue;
	return *this;
}
float Vector2::Length()
{
	float fDistance = sqrt(x * x + y * y);
	return fDistance;
}
static float Length(Vector2& p)
{
	float fDistance = sqrt(p.x * p.x + p.y * p.y);
	return fDistance;
}
Vector2::Vector2() {}
Vector2::Vector2(float fx, float fy)
{
	x = fx;
	y = fy;
}



float Vector3::operator | (Vector3 const& p) {
	return (this->x * p.x + this->y * p.y + this->z * p.z);
}
Vector3 Vector3::operator ^ (Vector3 const& p) {
	return Vector3(y * p.z - p.y * z,
		z * p.x - x * p.z,
		x * p.y - y * p.x);
}
bool Vector3::operator ==(Vector3& p) {
	if (fabs(x - p.x) > EPSILON) return false;
	if (fabs(y - p.y) > EPSILON) return false;
	if (fabs(z - p.z) > EPSILON) return false;
	return true;
}
bool Vector3::operator !=(Vector3& p) {
	return !(*this == p);
}
Vector3 Vector3::operator +(Vector3& p) {
	return Vector3(x + p.x,
		y + p.y,
		z + p.z);
}
Vector3 Vector3::operator -(Vector3& p) {
	return Vector3(x - p.x,
		y - p.y,
		z - p.z);
}
Vector3 Vector3::operator *(float f) {
	return Vector3(x * f,
		y * f,
		z * f);
}
Vector3 Vector3::operator /(float f) {
	return Vector3(x / f,
		y / f,
		z / f);
}
Vector3& Vector3::operator *=(float f) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
Vector3& Vector3::operator /=(float f) {
	x /= f;
	y /= f;
	z /= f;
	return *this;
}
Vector3& Vector3::operator +=(Vector3 p) {
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}
Vector3 Vector3::operator*(Matrix const& m)
{
	Vector4 t;
	t.x = x * m._11 + y * m._21 + z * m._31 + 1.0f * m._41;
	t.y = x * m._12 + y * m._22 + z * m._32 + 1.0f * m._42;
	t.z = x * m._13 + y * m._23 + z * m._33 + 1.0f * m._43;
	t.w = x * m._14 + y * m._24 + z * m._34 + 1.0f * m._44;

	if (fabs(t.w - 0.0f) > EPSILON) // t.w가 0이 아니라면
	{
		t.x /= t.w;
		t.y /= t.w;
		t.z /= t.w;
		t.w /= t.w;
	}
	return Vector3();
}
float Vector3::Angle(Vector3& p) {
	Vector3 a = NormVector();
	Vector3 b = p.NormVector();
	float fDot = a | b;
	if (fDot > 1.0f) fDot = 1.0f;
	float fRadian = acos(fDot);
	float fAngle = RadianToDegree(fRadian);

	// 벡터의 외적을 사용하여 회전 방향을 결정
	Vector3 crossProduct = a ^ b;
	if (crossProduct.z < 0.0f) {
		// 시계 방향 회전
		fAngle = 360.0f - fAngle;
	}

	return fAngle;
}

float Vector3::Length() {
	float fDistance = sqrt(x * x + y * y + z * z);
	return fDistance;
}
void Vector3::Normalize() {
	float fInvertLength = 1.0f / Length();
	(*this) *= fInvertLength;
}
Vector3 Vector3::NormVector() {
	float fInvertLength = 1.0f / Length();
	return (*this) * fInvertLength;
}

static float GetDistance(Vector3& p) {
	float fDistance = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	return fDistance;
}

Vector3::Vector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}