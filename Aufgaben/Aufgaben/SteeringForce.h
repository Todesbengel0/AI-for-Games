#pragma once

#include "MoveBoundsFix.h"

struct SSteeringForce
{
	CHVector vMovementForce;
	float fRotationForce;

	bool bApplyRotationForce;
	bool bMoveByRot;

	MoveBoundsFix BoundsFix;

	inline SSteeringForce()
		: fRotationForce(0.0f) // CHVector is default constructed
		, bApplyRotationForce(false)
		, bMoveByRot(false)
		, BoundsFix(MoveBoundsFix::Clamp)
	{
	}
};
