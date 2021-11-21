#include "pch.h"
#include "SteeringBehaviorKinematicSEEK.h"
#include "KnowledgePosition.h"
#include "NPC.h"

CSteeringBehaviorKinematicSEEK::CSteeringBehaviorKinematicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::KinematicSeek)
	, m_pKnowledgePosition(target)
{
}

CSteeringBehaviorKinematicSEEK::~CSteeringBehaviorKinematicSEEK()
{
}

SSteeringForce CSteeringBehaviorKinematicSEEK::GetForce()
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	resForce.vMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// für korrekten Winkel muss Z-Achse invertiert werden
	CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();

	return resForce;
}
