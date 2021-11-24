#pragma once

struct SSteeringForce
{
	CHVector vMovementForce;
	float fRotationForce;
	bool bApplyRotationForce;

	inline SSteeringForce()
		: fRotationForce(0.0f) // CHVector is default constructed
		, bApplyRotationForce(true)
	{
	}
};
