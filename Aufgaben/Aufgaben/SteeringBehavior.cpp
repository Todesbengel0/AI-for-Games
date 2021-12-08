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
	if (force.Flags.bApplyRotationForce)
	{
		//Limit(force.fRotationForce, m_pUser->GetKinematics().GetMaxRotationForce());
		m_pUser->GetKinematics().ApplyRotationForce(force.fRotationForce, fTimeDelta);
	}
	else
	{
		m_pUser->GetKinematics().ChangeOrientation(force.fRotationForce);
	}

	// Bewegung nach Rotation ausrichten
	if (force.Flags.bMoveByRot)
	{
		// Bewegung bezüglich lokaler -Z Richtung
		force.vMovementForce = AngleVektoriaToVector(force.fRotationForce) * force.vMovementForce.Length();
	}

	// Bewegung
	Limit(force.vMovementForce, 0.0f, m_pUser->GetKinematics().GetMaxMovementForce());
	m_pUser->GetKinematics().ApplyMovementForce(force.vMovementForce, fTimeDelta, force.Flags.BoundsFix);
}

void CSteeringBehavior::Limit(CHVector& v, float minLength, float maxLength)
{
	assert(minLength < maxLength);

	const float fVLen = v.Length();

	float fFixedScale = 0.0f;
	if (minLength > 0.0f && fVLen < minLength)
	{
		fFixedScale = minLength;
	}
	else if (fVLen > maxLength)
	{
		fFixedScale = maxLength;
	}
	else
	{
		return;
	}

	ScaleVectorTo(v, fFixedScale);
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

	// Schei%&#! W-Komponente
	v.w = 0.0f;
	
	// Matrix auf Vektor anwenden
	v = mYRotMat * v;
}

void CSteeringBehavior::SmoothForceDelta(CHVector& vForce, const CKinematics& rKinematics, float fTimeDelta)
{
	CHVector vPreviousMovementForce = rKinematics.GetMovementForce();
	CHVector vDeltaForce = vForce - vPreviousMovementForce;

	// nur bei merkbarer Beschleunigungsänderung überprüfen
	constexpr float fCheckThreshold = 0.01f;
	if (vDeltaForce.Length() > fCheckThreshold)
	{
		// Beschleunigung
		if (vForce.Length() > vPreviousMovementForce.Length())
		{
			const float fMaxForce = std::min(vPreviousMovementForce.Length() + rKinematics.GetMaxMovementAcceleration() * fTimeDelta, rKinematics.GetMaxMovementForce());
			Limit(vForce, 0.0f, fMaxForce);
		}
		// Abbremsung
		/* else
		{
			const float fMinForce = std::max(vPreviousMovementForce.Length() - rKinematics.GetMaxMovementDeceleration() * fTimeDelta, 0.0f);
			Limit(vForce, fMinForce, FLT_MAX);
		}
		*/
	}

	// sollte nicht nötig sein, wird oben schon überprüft
	//Limit(vForce, 0.0f, rKinematics.GetMaxMovementForce());
}

void CSteeringBehavior::AccelerationThrottle(CHVector& vForce, float fTimeDelta)
{
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	// Wenn das Objekt anfängt zu laufen, soll es sich mit MinMovementForce bewegen (Startgeschwindigkeit)
	if (vPreviousMovementForce.Length() < m_pUser->GetKinematics().GetMinMovementForce())
	{
		ScaleVectorTo(vForce, m_pUser->GetKinematics().GetMinMovementForce());
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
