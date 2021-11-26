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

	// Bewegung nach Rotation ausrichten
	if (force.bMoveByRot)
	{
		// Force-Vector drehen
		CHMat mYRot(
			std::cosf(force.fRotationForce), 0.0f, std::sinf(force.fRotationForce), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-std::sinf(force.fRotationForce), 0.0f, std::cosf(force.fRotationForce), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		force.vMovementForce = mYRot * force.vMovementForce;
		//force.fRotationForce = GetAngleDirectionByZAxis(force.vMovementForce);
	}

	// Bewegung
	Limit(force.vMovementForce, m_pUser->GetKinematics().GetMaxMovementForce());
	m_pUser->GetKinematics().ApplyMovementForce(force.vMovementForce, fTimeDelta);

	// Ausrichtung / Rotation
	if (force.bApplyRotationForce)
	{
		//Limit(force.fRotationForce, m_pUser->GetKinematics().GetMaxRotationForce());
		m_pUser->GetKinematics().ApplyRotationForce(force.fRotationForce, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(0*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(1*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(2*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(3*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(5*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(-1*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(-3*HALFPI, fTimeDelta);
		//m_pUser->GetKinematics().ApplyRotationForce(-5*HALFPI, fTimeDelta);
	}
	else
	{
		m_pUser->GetKinematics().ChangeOrientation(force.fRotationForce);
	}
}

void CSteeringBehavior::Limit(CHVector& v, float maxLength)
{
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

float CSteeringBehavior::GetAngleDirectionByXZ(CHVector v)
{
	v.z = -v.z;
	return v.AngleXZ();
}
