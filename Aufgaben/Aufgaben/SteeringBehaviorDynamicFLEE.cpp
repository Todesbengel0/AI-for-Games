#include "pch.h"
#include "SteeringBehaviorDynamicFLEE.h"
#include "KnowledgesInclude.h"
#include "Npc.h"

CSteeringBehaviorDynamicFLEE::CSteeringBehaviorDynamicFLEE(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::DynamicFlee)
	, m_pKnowledgePosition(target)
{
}

CSteeringBehaviorDynamicFLEE::~CSteeringBehaviorDynamicFLEE()
{
}

SSteeringForce CSteeringBehaviorDynamicFLEE::GetForce()
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// bewegung zum ziel
	resForce.vMovementForce = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vCurMovementForce;

	// schönere Mittlung mit /2 (kein ARRIVE notwendig), aber nicht gefragt
	//resForce.vMovementForce *= 0.5f;
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// für korrekten Winkel muss Z-Achse invertiert werden
	CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();

	return resForce;
}
