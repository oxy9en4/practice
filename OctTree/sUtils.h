#pragma once
#define randstep(fmin, fmax) ((float)fmin+((float)fmax*(float)fmin)*rand() / RAND_MAX)

// operator overloading
struct sPoint {
	float x;
	float y;
	sPoint operator+(sPoint& p) {
		return sPoint(x + p.x, y + p.y);
	}
	sPoint& operator+=(sPoint& p) {
		x += p.x;
		y += p.y;
		return *this;
	}
	sPoint operator-(sPoint& p) {
		return sPoint(x - p.x, y - p.y);
	}
	sPoint operator*(float fv) {
		return sPoint(x * fv, y * fv);
	}
	sPoint operator/(float fv) {
		return sPoint(x / fv, y / fv);
	}
	sPoint operator/=(float fv) {
		x = x / fv;
		y = y / fv;
		return *this;
	}
	float getDistance() {
		float fDistance = sqrt(x * x + y * y);
		return fDistance;
	}
	static float getDistance(sPoint& d) {
		float fDistance = sqrt(d.x * d.x + d.y * d.y);
		return fDistance;
	}

	
	sPoint(float fx, float fy) : x(fx), y(fy) {}
	sPoint() {};
};  

struct sRect {
	float fx;
	float fy;
	float fWidth;
	float fHeight;
	sPoint Point[NTREE];
	sPoint Center;
	sPoint Half;
	sPoint Min;
	sPoint Max;
	sPoint v;
	sPoint s;

	void Set(float x, float y, float w, float h) {
		v = { x, y };
		s = { w, h };

		fx = x;
		fy = y;
		fWidth = w;
		fHeight = h;

		Point[0] = { fx, fy };
		Point[1] = { fx + fWidth, fy };
		Point[2] = { fx + fWidth, fy + fHeight };
		Point[3] = { fx, fy + fHeight };
		Half = { fWidth * 0.5f, fHeight * 0.5f };
		Center = { (Point[0] + Point[2]) * 0.5f };
		Min = Point[0];
		Max = Point[2];
	}

	sRect() {}
	sRect(float x, float y, float w, float h) {
		Set(x, y, w, h);
	}
};

class sUtils
{

};

