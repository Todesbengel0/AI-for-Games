#include "pch.h"
#include "Kinematics.h"

CKinematics::CKinematics()
{

}

CKinematics::~CKinematics()
{

}

CHVector CKinematics::GetPosition()
{
	return GetPos();
}

float CKinematics::GetOrientation()
{
	CHVector vDir = -GetDirection();
	//std::atan2f(std::sqrtf( , vDir.y)
	return vDir.AngleZX();
}

CHVector CKinematics::GetMovementForce()
{
	return m_MovementForce;
}

float CKinematics::GetRotationVelocity()
{
	return m_RotationVelocity;
}

void CKinematics::SetOrientation(float fAngle)
{
	float fAngleDelta = fAngle - GetOrientation();
	RotateYDelta(fAngleDelta);
}

void CKinematics::SetMovementForce(CHVector vMovementForce)
{
	m_MovementForce = vMovementForce;
}

void CKinematics::SetRotationVelocity(float vel)
{
	m_RotationVelocity = vel;
}

void CKinematics::SetMaxMovementForce(float force)
{
	m_MaxMovementForce = force;
}

void CKinematics::SetMaxRotationVelocity(float vel)
{
	m_MaxRotationVelocity = vel;
}
