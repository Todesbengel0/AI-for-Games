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

//void CSteeringBehavior::Limit(CHVector& v, float maxLength)
//{
//	if (v.Length() <= maxLength)
//		return;
//
//	v.Norm();
//	v *= maxLength;
//}

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
