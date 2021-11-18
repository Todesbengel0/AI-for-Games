#pragma once

class CKinematics : public CPlacement
{
public:
	CKinematics();
	~CKinematics();

public:
	CHVector GetPosition();
	float GetOrientation();
	CHVector GetMovementForce();
	float GetRotationVelocity();
	float GetMaxMovementForce();
	float GetMaxRotationVelocity();

	void SetOrientation(float fAngle);
	void SetMovementForce(CHVector vMovementForce);
	void SetRotationVelocity(float vel);
	void SetMaxMovementForce(float force);
	void SetMaxRotationVelocity(float vel);

private:
	CHVector m_MovementForce;
	float m_RotationVelocity;

	float m_MaxMovementForce;
	float m_MaxRotationVelocity;
};
