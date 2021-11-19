#include "pch.h"
#include "SteeringBehaviorKinematicFLEE.h"
#include "KnowledgePosition.h"
#include "NPC.h"

CSteeringBehaviorKinematicFLEE::CSteeringBehaviorKinematicFLEE(CNpc* user)
	: CSteeringBehavior(user),
	m_pKnowledgePosition(nullptr)
{
}

CSteeringBehaviorKinematicFLEE::~CSteeringBehaviorKinematicFLEE()
{
}

CHVector CSteeringBehaviorKinematicFLEE::GetForce()
{
	CHVector vTargetDir = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();
	vTargetDir.Norm();
	vTargetDir *= m_pUser->GetKinematics().GetMaxMovementForce();
	m_pUser->GetKinematics().SetMovementForce(vTargetDir);
	m_pUser->GetKinematics().SetOrientation(0.0f);
	return vTargetDir;
}

void CSteeringBehaviorKinematicFLEE::SetKnowledgePosition(CKnowledgePosition* target)
{
	m_pKnowledgePosition = target;
}
