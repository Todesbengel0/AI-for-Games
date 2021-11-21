#include "pch.h"
#include "Kinematics.h"

CKinematics::CKinematics()
	: m_MovementForce(0.0f, 0.0f, 0.0f)
	, m_RotationVelocity(0.0f)
{
	SetMaxMovementForce(1.0f);
	SetMaxRotationVelocity(1.0f);

	m_zpPos.AddPlacement(&m_zpRot);
}

void CKinematics::ResetPosRot()
{
	// should reset all transformations on the mats
	m_zpPos.Translate(0.0f, 0.0f, 0.0f);
	m_zpRot.Translate(0.0f, 0.0f, 0.0f);
}

CKinematics::~CKinematics()
{
}

CPlacement& CKinematics::GetTopPlacement()
{
	return m_zpPos;
}

CPlacement& CKinematics::GetLowestPlacement()
{
	return m_zpRot;
}

CHVector CKinematics::GetPosition()
{
	return m_zpPos.GetPos();
}

float CKinematics::GetOrientation()
{
	CHVector vDir = -m_zpRot.GetDirection();
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

float CKinematics::GetMaxMovementForce()
{
	return m_zpPos.GetTranslationSensitivity();
}

float CKinematics::GetMaxRotationVelocity()
{
	return m_zpPos.GetRotationSensitivity();
}

void CKinematics::SetBounds(CHVector vMin, CHVector vMax)
{
	m_zpPos.SetMoveRange(CAABB(vMin, vMax));
}

void CKinematics::ChangeOrientation(float fAngle)
{
	//float fAngleDelta = fAngle - GetOrientation();
	//m_zpRot.RotateYDelta(fAngleDelta);
	m_zpRot.RotateY(fAngle);
}

void CKinematics::ApplyMovementForce(CHVector vMovementForce)
{
	m_MovementForce = vMovementForce;
	m_zpPos.TranslateDelta(vMovementForce);

	// sicherstellen, dass bewegung in grenzen bleibt
	ClampInBounds();
}

void CKinematics::SetRotationVelocity(float vel)
{
	m_RotationVelocity = vel;
}

void CKinematics::SetMaxMovementForce(float force)
{
	m_zpPos.SetTranslationSensitivity(force);
	m_zpRot.SetTranslationSensitivity(force);
}

void CKinematics::SetMaxRotationVelocity(float vel)
{
	m_zpPos.SetRotationSensitivity(vel);
	m_zpRot.SetRotationSensitivity(vel);
}

void CKinematics::ClampInBounds()
{
	float fMinXDiff = m_zpPos.m_aabbMove.GetMin().x - m_zpPos.GetPos().x;
	if (fMinXDiff > 0.0f)
		m_zpPos.TranslateXDelta(fMinXDiff);

	float fMaxXDiff = m_zpPos.m_aabbMove.GetMax().x - m_zpPos.GetPos().x;
	if (fMaxXDiff < 0.0f)
		m_zpPos.TranslateXDelta(fMaxXDiff);

	float fMinZDiff = m_zpPos.m_aabbMove.GetMin().z - m_zpPos.GetPos().z;
	if (fMinZDiff > 0.0f)
		m_zpPos.TranslateZDelta(fMinZDiff);

	float fMaxZDiff = m_zpPos.m_aabbMove.GetMax().z - m_zpPos.GetPos().z;
	if (fMaxZDiff < 0.0f)
		m_zpPos.TranslateZDelta(fMaxZDiff);
}
