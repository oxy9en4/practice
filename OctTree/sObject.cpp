#include "stdafx.h"
#include "sObject.h"


void sObject::SetRect(sPoint& c, float w, float h) {
	rect.Set(c, w, h);
}

void sDynamicObject::Move(float fSecond) {
	sPoint vDir = Target - Position;
	float fD = vDir.getDistance();

	sPoint vVelocity = Direction * fSpeed;
	Position += vVelocity;
	rect.Set(Position, rect.fWidth, rect.fHeight);

	if (Position.x < 0.0f) {
		Direction.x *= -1.0f;
		Position.x = 0.0f;
	}
	if (Position.y < 0.0f) {
		Direction.y *= -1.0f;
		Position.y = 0.0f;
	}
	if (Position.x > 800.0f) {
		Direction.x *= -1.0f;
		Position.x = 800.0f;
	}
	if (Position.y > 600.0f) {
		Direction.y *= -1.0f;
		Position.y = 600.0f;
	}
}

void sDynamicObject::SetTarget(sPoint& t) {
	Target = t;
	Direction = Target - Position;
	float fDistacne = Direction.getDistance();
	Direction /= fDistacne; // ¡§±‘»≠
}