#include "pch.h"
#include "SteeringBehaviorKinematicSEEK.h"

CSteeringBehaviorKinematicSEEK::CSteeringBehaviorKinematicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::KinematicSeek)
	, m_pKnowledge(target)
{

}

CSteeringBehaviorKinematicSEEK::~CSteeringBehaviorKinematicSEEK()
{
}

SSteeringForce CSteeringBehaviorKinematicSEEK::GetForce()
{
	return SSteeringForce();
}
