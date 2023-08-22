
#include "Math.h"

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
float Vector3::Angle(Vector3& p) {
	Vector3 a = NormVector();
	Vector3 b = p.NormVector();
	float fCosAngle = a | b;
	float fRadian = acos(fCosAngle);
	float fDegree = RadianToDegree(fRadian);
	return fDegree;
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