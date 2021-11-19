#include "pch.h"
#include "SteeringBehaviorKinematicSEEK.h"

CSteeringBehaviorKinematicSEEK::CSteeringBehaviorKinematicSEEK(CNpc* user)
	: CSteeringBehavior(user),
	m_pKnowledge(nullptr)
{

}

CSteeringBehaviorKinematicSEEK::~CSteeringBehaviorKinematicSEEK()
{
}

CHVector CSteeringBehaviorKinematicSEEK::GetForce()
{

}

void CSteeringBehaviorKinematicSEEK::SetKnowledgePosition(CKnowledgePosition* target)
{
	m_pKnowledge = target;
}
