#pragma once

struct SSteeringForce
{
	CHVector vMovementForce;
	float fRotationForce;

	inline SSteeringForce()
		: fRotationForce(0.0f) // CHVector is default constructed
	{
	}
};
