#pragma once

class CKinematics
{
public:
	CKinematics();
	~CKinematics();

public:


private:
	CHVector m_Position;
	float m_Orientation;
	CHVector m_MovementVelocity;
	float m_RotationVelocity;

	float m_MaxMovementVelocity;
	float m_MaxRotationVelocity;
};
