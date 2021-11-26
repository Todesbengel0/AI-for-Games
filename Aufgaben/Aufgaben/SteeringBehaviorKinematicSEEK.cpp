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

SSteeringForce CSteeringBehaviorKinematicSEEK::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	resForce.vMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// Skalarwinkel des Kraftvektors
	resForce.fRotationForce = GetAngleDirectionByXZ(resForce.vMovementForce);
	resForce.bApplyRotationForce = false;

	return resForce;
}
