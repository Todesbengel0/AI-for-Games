#include "pch.h"
#include "SteeringBehaviorDynamicSEEK.h"
#include "Npc.h"
#include "KnowledgesInclude.h"

CSteeringBehaviorDynamicSEEK::CSteeringBehaviorDynamicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::DynamicSeek)
	, m_pKnowledgePosition(target)
{
}

CSteeringBehaviorDynamicSEEK::~CSteeringBehaviorDynamicSEEK()
{
}

SSteeringForce CSteeringBehaviorDynamicSEEK::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// bewegung zum ziel
	resForce.vMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vCurMovementForce;

	// schönere Mittlung mit /2 (kein ARRIVE notwendig), aber nicht gefragt
	//resForce.vMovementForce *= 0.5f;
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// Skalarwinkel des Kraftvektors
	resForce.fRotationForce = GetAngleDirectionByZAxis(resForce.vMovementForce);

	return resForce;
}
