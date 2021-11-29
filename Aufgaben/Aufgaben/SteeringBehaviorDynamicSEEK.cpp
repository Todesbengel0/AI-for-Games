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

	// Bewegung zum Ziel
	CHVector vToPlayer = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	vToPlayer += vCurMovementForce;
	// schönere Mittlung mit /2 (kein ARRIVE notwendig), aber nicht gefragt
	//vToPlayer *= 0.5f;
	vToPlayer.Norm();
	
	// neue Bewegungskraft aus mittel mit max. Geschwindigkeit
	resForce.vMovementForce = vToPlayer * m_pUser->GetKinematics().GetMaxMovementForce();
	resForce.bMoveByRot = false;	// kein Überschreiben durch SteeringBehavior

	// Skalarwinkel des Kraftvektors
	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
	resForce.bApplyRotationForce = false;	// direkte Richtungsänderung

	return resForce;
}
