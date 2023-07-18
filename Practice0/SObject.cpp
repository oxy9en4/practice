#include "stdafx.h"
#include "SObject.h"


void SObject::SetRect(SPoint& p, float w, float h) {
	mCollisionBox.Set(p, w, h);
}

void SDynamicObject::SetTarget(SPoint& p) {
	mTarget = p;
	mDirection = p - mPivot;
	float magnitude = mDirection.GetDistance();
	mDirection /= magnitude;
}


void SDynamicObject::Move(float fSecond) {
	SPoint vVelocity = mDirection * mFspeed * fSecond;
	mPivot = mPivot + vVelocity;
	
	if (mPivot.x < 0) {
		mDirection.x *= -1.0f;
		mPivot.x = 0.0f;
	}
	if (mPivot.y < 0) {
		mDirection.y *= -1.0f;
		mPivot.y = 0.0f;
	}
	if (mPivot.x > 800) {
		mDirection.x *= -1.0f;
		mPivot.x = 800;
	}
	if (mPivot.y > 600) {
		mDirection.y *= -1.0f;
		mPivot.y = 600;
	}
}

