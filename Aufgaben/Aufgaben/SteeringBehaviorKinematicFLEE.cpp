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

SSteeringForce CSteeringBehaviorKinematicFLEE::GetForce()
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	//CHVector vTargetDir = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();
	//vTargetDir.Norm();
	//vTargetDir *= m_pUser->GetKinematics().GetMaxMovementForce();
	//m_pUser->GetKinematics().SetMovementForce(vTargetDir);
	//m_pUser->GetKinematics().SetOrientation(0.0f);

	resForce.vMovementForce = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	resForce.fRotationForce = 0.0f;

	return resForce;
}
