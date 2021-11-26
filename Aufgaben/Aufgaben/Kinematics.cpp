#include "pch.h"
#include "Kinematics.h"

CKinematics::CKinematics()
	: m_MovementForce(0.0f, 0.0f, 0.0f)
	, m_RotationForce(0.0f)
	, m_MaxMovementAcceleration(1.0f)
{
	SetMaxMovementForce(1.0f);
	SetMaxRotationForce(1.0f);

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

CHVector CKinematics::GetOrientationVec()
{
	// Lokale Richtung des Placements bezüglich lokaler -Z Achse
	return m_zpRot.GetDirection();
}

float CKinematics::AngleVektoriaToZX(CHVector vVektoriaDirection)
{
	// Vektoria Placement Ausrichtung ist (warum auch immer) standardmäßig relativ zur -Z Achse
	// Für unsere Berechnungen wollen wir gerne Winkel bezüglich der +X Achse

	// Zuerst -Z nach +Z, dann projiziert an XZ Ebene mit 0 = Z-Achse
	return (-vVektoriaDirection).AngleZX();
}

float CKinematics::GetOrientationAngleZX()
{
	return AngleVektoriaToZX(GetOrientationVec());
	//CHVector vDir = -m_zpRot.GetDirection();
	////std::atan2f(std::sqrtf( , vDir.y)
	//return vDir.AngleZX();
}

CHVector CKinematics::GetMovementForce()
{
	return m_MovementForce;
}

float CKinematics::GetRotationForce()
{
	return m_RotationForce;
}

float CKinematics::GetMaxMovementForce()
{
	return m_zpPos.GetTranslationSensitivity();
}

float CKinematics::GetMaxRotationForce()
{
	return m_zpPos.GetRotationSensitivity();
}

float CKinematics::GetMaxMovementAcceleration()
{
	return m_MaxMovementAcceleration;
}

void CKinematics::SetPosition(CHVector vPos)
{
	m_zpPos.Translate(vPos);
}

void CKinematics::SetBounds(CHVector vMin, CHVector vMax)
{
	m_zpPos.SetMoveRange(CAABB(vMin, vMax));
}

void CKinematics::ChangeOrientation(float fAngle)
{
	m_zpRot.RotateY(fAngle);
}

void CKinematics::ApplyMovementForce(CHVector vMovementForce, float fTimeDelta)
{
	m_MovementForce = vMovementForce;
	m_zpPos.TranslateDelta(vMovementForce * fTimeDelta);

	// sicherstellen, dass bewegung in grenzen bleibt
	ClampInBounds();
}

void CKinematics::ApplyRotationForce(float vel, float fTimeDelta)
{
	m_RotationForce = vel;

	//float fAngleDiff = m_RotationForce - GetOrientationAngle();
	float fAngleDiff = AngleDiff(GetOrientationAngleZX(), m_RotationForce);
	m_zpRot.RotateYDelta(fAngleDiff * fTimeDelta);
}

float CKinematics::AngleDiff(float aSource, float aTarget)
{
	//return std::atan2f(std::sinf(a2 - a1), std::cosf(a2 - a1));
	float a = aTarget - aSource;

	if (a > PI) a -= TWOPI;
	else if (a < -PI) a += TWOPI;

	return a;
}

void CKinematics::SetMaxMovementForce(float force)
{
	m_zpPos.SetTranslationSensitivity(force);
	m_zpRot.SetTranslationSensitivity(force);
}

void CKinematics::SetMaxRotationForce(float vel)
{
	m_zpPos.SetRotationSensitivity(vel);
	m_zpRot.SetRotationSensitivity(vel);
}

void CKinematics::SetMaxMovementAcceleration(float acceleration)
{
	m_MaxMovementAcceleration = acceleration;
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
