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

SSteeringForce CSteeringBehaviorKinematicFLEE::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// Rotation zum Spieler
	CHVector vAwayFromPlayer = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();
	resForce.fRotationForce = AngleVektoriaToZX(vAwayFromPlayer);
	resForce.Flags.bApplyRotationForce = false;

	// Laufe mit max. Geschwindigkeit in die Richtung
	// wird durch CSteeringBehavior::Update nach fRotationForce verrechnet
	// muss lediglich Länge übergeben
	resForce.Flags.bMoveByRot = true;
	resForce.vMovementForce = CHVector(m_pUser->GetKinematics().GetMaxMovementForce(), 0.0f, 0.0f);

	return resForce;
}
