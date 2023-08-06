#include "stdafx.h"
#include "Object.h"

void Object::SetBox(Vector3& vPos, float w, float h, float d) {
	mBox.Set(vPos, w, h, d);
}

void DynamicObject::Move(float fSPF)
{
	Vector3 vVelocity = mDirection * fSPF * fSpeed;
	vVelocity += mBox.v;
	if (vVelocity.x < 0.0f) {
		vVelocity.x = 0.0f;
		mDirection.x *= -1.0f;
	}
	if (vVelocity.x > 800.0f) {
		vVelocity.x = 800.0f;
		mDirection.x *= -1.0f;
	}
	if (vVelocity.y < 0.0f) {
		vVelocity.y = 0.0f;
		mDirection.y *= -1.0f;
	}
	if (vVelocity.y > 600.0f) {
		vVelocity.y = 600.0f;
		mDirection.y *= -1.0f;
	}
	if (vVelocity.z < 0.0f) {
		vVelocity.z = 0.0f;
		mDirection.z *= -1.0f;
	}
	if (vVelocity.z > 600.0f) {
		vVelocity.z = 600.0f;
		mDirection.z *= -1.0f;
	}
	// 범위를 벗어나면 방향 반대로, 위치 조정
	mBox.Set(vVelocity, mBox.size.x, mBox.size.y, mBox.size.z); // 새로운 위치로 재정의

	// 충돌 검사?
	
}

void DynamicObject::SetTarget(Vector3& vTarget)
{
	this->mTarget = vTarget;
	mDirection = mTarget - mBox.v;
	mDirection /= mDirection.Length(); // 정규화 Normalize
}
