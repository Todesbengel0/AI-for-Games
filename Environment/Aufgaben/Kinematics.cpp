#include "pch.h"
#include "Kinematics.h"

CKinematics::CKinematics()
	: m_MovementForce(0.0f, 0.0f, 0.0f, 0.0f)
	, m_RotationForce(0.0f)
	, m_MinMovementForce(1.0f)
	, m_MaxMovementAcceleration(2.0f)
	, m_MaxMovementDeceleration(10.0f)
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

	// reset forces as well
	m_MovementForce = CHVector(0.0f, 0.0f, 0.0f, 0.0f);
	m_RotationForce = 0.0f;
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

float CKinematics::GetOrientationAngleZX()
{
	return AngleVektoriaToZX(GetOrientationVec());
	//CHVector vDir = -m_zpRot.GetDirection();
	////std::atan2f(std::sqrtf( , vDir.y)
	//return vDir.AngleZX();
}

CHVector CKinematics::GetMovementForce() const
{
	return m_MovementForce;
}

float CKinematics::GetRotationForce() const
{
	return m_RotationForce;
}

float CKinematics::GetMaxMovementForce() const
{
	return const_cast<CPlacement&>(m_zpPos).GetTranslationSensitivity();
}

float CKinematics::GetMaxRotationForce() const
{
	return const_cast<CPlacement&>(m_zpPos).GetRotationSensitivity();
}

float CKinematics::GetMinMovementForce() const
{
	return m_MinMovementForce;
}

float CKinematics::GetMaxMovementAcceleration() const
{
	return m_MaxMovementAcceleration;
}

float CKinematics::GetMaxMovementDeceleration() const
{
	return m_MaxMovementDeceleration;
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

void CKinematics::ApplyMovementForce(CHVector vMovementForce, float fTimeDelta, MoveBoundsFix eBoundsFix /*= MoveBoundsFix::Clamp*/)
{
	assert(std::abs(vMovementForce.w) < 0.01f);

	m_MovementForce = vMovementForce;
	m_zpPos.TranslateDelta(vMovementForce * fTimeDelta);

	// sicherstellen, dass bewegung in grenzen bleibt
	CheckBounds(eBoundsFix, fTimeDelta);
}

void CKinematics::ApplyRotationForce(float vel, float fTimeDelta)
{
	m_RotationForce = vel;

	//float fAngleDiff = m_RotationForce - GetOrientationAngle();
	float fAngleDiff = AngleDiff(GetOrientationAngleZX(), m_RotationForce);
	m_zpRot.RotateYDelta(fAngleDiff * fTimeDelta);
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

void CKinematics::SetMinMovementForce(float force)
{
	m_MinMovementForce = force;
}

void CKinematics::SetMaxMovementIncrease(float acceleration)
{
	m_MaxMovementAcceleration = acceleration;
}

void CKinematics::SetMaxMovementDecrease(float time)
{
	m_MaxMovementDeceleration = time;
}

void CKinematics::CheckBounds(MoveBoundsFix eBoundsFix, float fTimeDelta)
{
	// out of left bound
	float fDiff = m_zpPos.m_aabbMove.GetMin().x - m_zpPos.GetPos().x;
	if (fDiff > 0.0f)
	{
		m_zpPos.TranslateXDelta(fDiff);
		if (eBoundsFix == MoveBoundsFix::Bounce)
			MultiplyApplyMovementForce(CHVector(-1.0f, 1.0f, 1.0f, 0.0f), fTimeDelta);
	}

	// out of right bound
	fDiff = m_zpPos.m_aabbMove.GetMax().x - m_zpPos.GetPos().x;
	if (fDiff < 0.0f)
	{
		m_zpPos.TranslateXDelta(fDiff);
		if (eBoundsFix == MoveBoundsFix::Bounce)
			MultiplyApplyMovementForce(CHVector(-1.0f, 1.0f, 1.0f, 0.0f), fTimeDelta);
	}

	// out of bottom bound
	fDiff = m_zpPos.m_aabbMove.GetMin().z - m_zpPos.GetPos().z;
	if (fDiff > 0.0f)
	{
		m_zpPos.TranslateZDelta(fDiff);
		if (eBoundsFix == MoveBoundsFix::Bounce)
			MultiplyApplyMovementForce(CHVector(1.0f, 1.0f, -1.0f, 0.0f), fTimeDelta);
	}

	// out of top bound
	fDiff = m_zpPos.m_aabbMove.GetMax().z - m_zpPos.GetPos().z;
	if (fDiff < 0.0f)
	{
		m_zpPos.TranslateZDelta(fDiff);
		if (eBoundsFix == MoveBoundsFix::Bounce)
			MultiplyApplyMovementForce(CHVector(1.0f, 1.0f, -1.0f, 0.0f), fTimeDelta);
	}
}

void CKinematics::MultiplyApplyMovementForce(CHVector vFactor, float fTimeDelta, bool bFixOrientation /*= true*/)
{
	// vorherige reine Richtungsänderung
	//ChangeOrientation(AngleVektoriaToZX(MultiplyElements(GetOrientationVec(), CHVector(-1.0f, 1.0f, 1.0f, 0.0f))));

	CHVector vNewMovementForce = MultiplyElements(m_MovementForce, vFactor);
	ApplyMovementForce(vNewMovementForce, fTimeDelta);
	if (bFixOrientation)
		ChangeOrientation(AngleVektoriaToZX(vNewMovementForce));
}

void CKinematics::BounceOff(CHVector vRef)
{
	CHVector vDir = GetOrientationVec();
	float fDot = vDir * vRef;
	CHVector vReflected = vDir - (vRef * (2.0f * fDot));

	ChangeOrientation(AngleVektoriaToZX(vReflected));
	//ApplyMovementForce(vReflected * std::max(m_MovementForce.Length(), 0.2f), 1.0f, MoveBoundsFix::Clamp);
}
