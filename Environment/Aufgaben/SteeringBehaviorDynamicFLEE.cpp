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

SSteeringForce CSteeringBehaviorDynamicFLEE::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// Bewegung zum Ziel
	CHVector vAwayFromPlayer = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	vAwayFromPlayer += vCurMovementForce;
	ScaleVectorTo(vAwayFromPlayer, m_pUser->GetKinematics().GetMaxMovementForce());

	// neue Bewegungskraft aus mittel mit max. Geschwindigkeit
	resForce.vMovementForce = vAwayFromPlayer;
	resForce.Flags.bMoveByRot = false;	// kein Überschreiben durch SteeringBehavior

	// Skalarwinkel des Kraftvektors
	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
	resForce.Flags.bApplyRotationForce = false;	// direkte Richtungsänderung

	return resForce;
}
