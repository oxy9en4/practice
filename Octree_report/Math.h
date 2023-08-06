#pragma once


class Vector3
{
public:
	float x;
	float y;
	float z;


	float operator | (Vector3 const& p);
	Vector3 operator ^ (Vector3 const& p);

	bool operator ==(Vector3& p);
	bool operator !=(Vector3& p);
	Vector3 operator +(Vector3& p);
	Vector3 operator -(Vector3& p);
	Vector3 operator *(float f);
	Vector3 operator /(float f);
	Vector3& operator /=(float f);
	Vector3& operator *=(float f);
	Vector3& operator +=(Vector3 p);
	float Angle(Vector3& p);

	float Length();
	void Normalize();
	Vector3 NormVector();

	static float GetDistance(Vector3& p);
public:
	Vector3();
	Vector3(float fx, float fy, float fz);
	
};


class Math
{
};

