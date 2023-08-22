#pragma once
#include "stdafx.h"

class Vector2;
class Vector3;
class Vector4;
class Matrix;
class Ray;
class Plane;

struct Float2
{
	union
	{
		struct
		{
			float x;
			float y;
		};
		float v[2];
	};
};

struct Float3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};

struct Float4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};


struct Float4x4
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class Vector2 : public Float2
{
	bool operator == (Vector2& p);
	bool operator != (Vector2& p);
	Vector2 operator + (Vector2& p);
	Vector2 operator - (Vector2& p);
	Vector2 operator * (float fValue);
	Vector2 operator / (float fValue);
	Vector2& operator /= (float fValue);
public:
	float Length();
	static float Length(Vector2& p);
public:
	Vector2();
	Vector2(float fx, float fy);
};

class Vector3 : public Float3
{
public:


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

class Vector4 : public Float4
{
public:
	Vector4()
	{
		x = y = z = 0.0f;
	}
	Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}
};

class Ray
{
public:
	Vector3 vPosition;
	Vector3 vDirection;
	float GetDistance(Vector3& p0)
	{
		Vector3 v = p0 - vPosition;
		float k = ((v | vDirection) / (vDirection | vDirection));
		Vector3 p = vDirection * k;
		Vector3 w = v - p;
		return w.Length();
	}
	Ray() {};
	Ray(Vector3 p, Vector3 d)
	{
		vPosition = p;
		vDirection = d;
	}
};

class Plane
{
	Vector3 vPos;
	Vector3 vNor;
	float a, b, c, d;
	float GetDistance(Vector3& v)
	{
		return a * v.x + b * v.y + c * v.z + d; // 단위벡터의 경우 분모가 1이므로 해당 식으로 갈음
	}
	Plane() {};
	Plane(Vector3 vP, Vector3 vD)
	{
		vNor = vD.NormVector();
		vPos = vP;
		a = vNor.x;
		b = vNor.y;
		c = vNor.z;
		d = -(vNor | vPos);
	}
	// 시계방향으로 구성되어 있어야 한다.
	//     p0
	 //p1      p2

	Plane(Vector3 p0, Vector3 p1, Vector3 p2)
	{
		vPos = p0;
		Vector3 e1 = p1 - p0;
		Vector3 e2 = p2 - p0;
		vNor = (e1 ^ e2).NormVector();
		a = vNor.x;
		b = vNor.y;
		c = vNor.z;
		d = -(vNor | vPos);
	}
};

class Matrix : public Float4x4
{
	Matrix()
	{
		Identity();
	}
	void Identity()
	{
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
		_11 = _22 = _33 = _44 = 1.0f;
	}
	Matrix operator *(Matrix const& matrix) {
		Matrix ret;
		for (int iColumn = 0; iColumn < 4; iColumn++)
		{
			for (int iRow = 0; iRow < 4; iRow++)
			{
				ret.m[iRow][iColumn] =
					m[iRow][0] * matrix.m[0][iColumn] +
					m[iRow][1] * matrix.m[1][iColumn] +
					m[iRow][2] * matrix.m[2][iColumn] +
					m[iRow][3] * matrix.m[3][iColumn];
			}
		}
		return ret;

	}

	Vector3 operator* (Vector3 const& v)
	{
		Vector4 ret;
		ret.w = 1.0f;
		ret.x = v.x * _11 + v.y * _21 + v.z * _31 + 1.0f * _41;
		ret.y = v.x * _12 + v.y * _22 + v.z * _32 + 1.0f * _42;
		ret.z = v.x * _13 + v.y * _23 + v.z * _33 + 1.0f * _43;
		ret.w = v.x * _14 + v.y * _24 + v.z * _34 + 1.0f * _44;

		/* ret.x /= ret.w;
		 ret.y /= ret.w;
		 ret.z /= ret.w;
		 ret.w /= ret.w;*/

		return Vector3(ret.x, ret.y, ret.z);
	}
	float operator () (int iRow, int icol) const // indexing
	{
		return m[iRow][icol];
	}
	float& operator () (int iRow, int icol)
	{
		return m[iRow][icol];
	}

	void Translation(const Vector3& v)
	{
		_41 = v.x;
		_42 = v.y;
		_43 = v.z;
	}
	void Translation(float x, float y, float z)
	{
		_41 = x;
		_42 = y;
		_43 = z;
	}
	void Scale(const Vector3& v)
	{
		_11 = v.x;
		_22 = v.y;
		_33 = v.z;
	}
	void Scale(float x, float y, float z)
	{
		_11 = x;
		_22 = y;
		_33 = z;
	}
	void XRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_22 = fCos;  _23 = fSin;
		_32 = -fSin;  _33 = fCos;
	}
	void YRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_11 = fCos;  _13 = -fSin;
		_31 = fSin; _33 = fCos;
	}
	void ZRotate(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		_11 = fCos;  _12 = fSin;
		_21 = -fSin; _22 = fCos;
	}
	Matrix Transpose()
	{
		Matrix ret;
		ret._11 = _11; ret._12 = _21; ret._13 = _31; ret._14 = _41;
		ret._21 = _12; ret._22 = _22; ret._23 = _32; ret._24 = _42;
		ret._31 = _13; ret._32 = _23; ret._33 = _33; ret._34 = _43;
		ret._41 = _14; ret._42 = _24; ret._43 = _34; ret._44 = _44;
		return ret;
	}

};

class Math
{
};