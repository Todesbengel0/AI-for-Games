#include "pch.h"
#include "SteeringBehaviorKinematicFLEE.h"

CSteeringBehaviorKinematicFLEE::CSteeringBehaviorKinematicFLEE(CKnowledgePosition* pKnowledge)
	: m_pKnowledgePosition(pKnowledge)
{
}

CSteeringBehaviorKinematicFLEE::~CSteeringBehaviorKinematicFLEE()
{
}

CHVector CSteeringBehaviorKinematicFLEE::GetForce()
{
	CHVector vTargetDir = m_pKnowledgePosition->GetPos() - 
}
