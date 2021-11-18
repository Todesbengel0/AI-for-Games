#include "pch.h"
#include "SteeringBehaviorKinematicFLEE.h"
#include "NPC.h"

CSteeringBehaviorKinematicFLEE::CSteeringBehaviorKinematicFLEE(CKnowledgePosition* pKnowledge)
	: m_pKnowledgePosition(pKnowledge)
{
}

CSteeringBehaviorKinematicFLEE::~CSteeringBehaviorKinematicFLEE()
{
}

CHVector CSteeringBehaviorKinematicFLEE::GetForce()
{
	CHVector vTargetDir = m_user->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPos();
	vTargetDir.Norm();
	vTargetDir *= m_user->GetKinematics().GetMaxMovementForce();
	return vTargetDir;
}
