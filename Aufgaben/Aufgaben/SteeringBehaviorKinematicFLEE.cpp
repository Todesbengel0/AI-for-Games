#include "pch.h"
#include "SteeringBehaviorKinematicFLEE.h"
#include "KnowledgePosition.h"
#include "NPC.h"

CSteeringBehaviorKinematicFLEE::CSteeringBehaviorKinematicFLEE(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::KinematicFlee)
	, m_pKnowledgePosition(target)
{
}

CSteeringBehaviorKinematicFLEE::~CSteeringBehaviorKinematicFLEE()
{
}

SSteeringForce CSteeringBehaviorKinematicFLEE::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	resForce.vMovementForce = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// Skalarwinkel des Kraftvektors
	resForce.fRotationForce = GetAngleDirectionByZAxis(resForce.vMovementForce);
	resForce.bApplyRotationForce = false;

	return resForce;
}
