#pragma once

#include "MoveBoundsFix.h"

struct SSteeringForceFlags
{
	bool bApplyRotationForce;
	bool bMoveByRot;
	MoveBoundsFix BoundsFix;

	inline SSteeringForceFlags()
		: bApplyRotationForce(false)
		, bMoveByRot(false)
		, BoundsFix(MoveBoundsFix::Clamp)
	{
	}
};

struct SSteeringForce
{
	CHVector vMovementForce;
	float fRotationForce;

	SSteeringForceFlags Flags;

	inline SSteeringForce()
		: vMovementForce(0.0f, 0.0f, 0.0f, 0.0f) // W=0, da kein Punkt
		, fRotationForce(0.0f)
	{
	}

	inline SSteeringForce& operator+=(const SSteeringForce& rhs)
	{
		this->vMovementForce += rhs.vMovementForce;
		this->fRotationForce += rhs.fRotationForce;

		return *this;
	}
};

inline SSteeringForce operator+(const SSteeringForce& lhs, const SSteeringForce& rhs)
{
	SSteeringForce res;
	res.vMovementForce = const_cast<CHVector&>(lhs.vMovementForce) + rhs.vMovementForce;
	res.fRotationForce = lhs.fRotationForce + rhs.fRotationForce;
	return res;
}

inline SSteeringForce operator*(const SSteeringForce& lhs, float factor)
{
	SSteeringForce res;
	res.vMovementForce = const_cast<CHVector&>(lhs.vMovementForce) * factor;
	res.fRotationForce = lhs.fRotationForce * factor;
	return res;
}
