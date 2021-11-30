#include "pch.h"
#include "SteeringBehavior.h"
#include "Npc.h"

CSteeringBehavior::CSteeringBehavior(CNpc* user, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: CAction(user, npcAiMode)
{
}

CSteeringBehavior::~CSteeringBehavior()
{
}

void CSteeringBehavior::Update(float fTime, float fTimeDelta)
{
	SSteeringForce force = GetForce(fTimeDelta);

	// Keine Änderungen (vor allem des Winkels) wenn keine Kraft wirkt
	if (force.vMovementForce.Length() < 0.01f)
		return;

	// Ausrichtung / Rotation
	if (force.bApplyRotationForce)
	{
		//Limit(force.fRotationForce, m_pUser->GetKinematics().GetMaxRotationForce());
		m_pUser->GetKinematics().ApplyRotationForce(force.fRotationForce, fTimeDelta);
	}
	else
	{
		m_pUser->GetKinematics().ChangeOrientation(force.fRotationForce);
	}

	// Bewegung nach Rotation ausrichten
	if (force.bMoveByRot)
	{
		// Bewegung bezüglich lokaler -Z Richtung
		force.vMovementForce = AngleVektoriaToVector(force.fRotationForce) * force.vMovementForce.Length();
	}

	// Bewegung
	Limit(force.vMovementForce, 0.0f, m_pUser->GetKinematics().GetMaxMovementForce());
	m_pUser->GetKinematics().ApplyMovementForce(force.vMovementForce, fTimeDelta, force.BoundsFix);
}

void CSteeringBehavior::Limit(CHVector& v, float minLength, float maxLength)
{
	if (minLength > 0.0f && v.Length() < minLength)
	{
		v.Norm();
		v *= minLength;
	}

	if (v.Length() <= maxLength)
		return;

	v.Norm();
	v *= maxLength;
}

void CSteeringBehavior::Limit(float& angle, float maxAngle)
{
	if (angle < 0.0f)
		angle = std::max(angle, -maxAngle);
	else
		angle = std::min(angle, maxAngle);
}

void CSteeringBehavior::LimitToRotation(CHVector& v, float rotationAngle, float maxAngle)
{
	if (abs(rotationAngle) <= maxAngle)
		return;

	// Kleineren Drehwinkel zum angestrebten Rotationswinkel bestimmen,
	// um zu bestimmen, wie weit der bereits gedrehte Vektor in welche Richtung zurückgedreht werden muss
	float fBackwardRotation = rotationAngle - maxAngle;
	if (abs(rotationAngle + maxAngle) < abs(fBackwardRotation))
		fBackwardRotation = rotationAngle + maxAngle;

	// Rotationsmatrix zum Zurückdrehen bestimmen
	CHMat mYRotMat = CHMat(std::cosf(fBackwardRotation), 0, sinf(fBackwardRotation), 0, 0, 1, 0, 0, -sinf(fBackwardRotation), 0, cosf(fBackwardRotation), 0, 0, 0, 0, 1);
	
	// Matrix auf Vektor anwenden
	v = mYRotMat * v;
}

void CSteeringBehavior::BreakThrottle(CHVector& vForce, float fTimeDelta)
{
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	// Bestimmung der minimalen Geschwindigkeit, die angenommen werden darf
	// vorherige Geschwindigkeit * Beschleunigungsfaktor * Zeitunterschied
	vForce *= m_pUser->GetKinematics().GetMaxMovementDeceleration() * fTimeDelta;
}

void CSteeringBehavior::AccelerationThrottle(CHVector& vForce, float fTimeDelta)
{
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	// Wenn das Objekt anfängt zu laufen, soll es sich mit MinMovementForce bewegen (Startgeschwindigkeit)
	if (vPreviousMovementForce.Length() < m_pUser->GetKinematics().GetMinMovementForce())
	{
		vForce.Norm();
		vForce *= m_pUser->GetKinematics().GetMinMovementForce();
		return;
	}

	// Bestimmung der maximalen Geschwindigkeit, die angenommen werden darf
	// vorherige Geschwindigkeit + (Beschleunigungsfaktor - 1) * Zeitunterschied
	float fMaxMovementForce = vPreviousMovementForce.Length() + vPreviousMovementForce.Length() * (m_pUser->GetKinematics().GetMaxMovementAcceleration() - 1) * fTimeDelta;
	
	Limit(vForce, m_pUser->GetKinematics().GetMinMovementForce(), fMaxMovementForce);
}

float CSteeringBehavior::AngleDiffToPreviousForce(CHVector vForce)
{
	return AngleDiff(AngleVektoriaToZX(vForce), m_pUser->GetKinematics().GetOrientationAngleZX());
}
