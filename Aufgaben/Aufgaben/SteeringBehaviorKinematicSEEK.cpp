#include "pch.h"
#include "SteeringBehaviorKinematicSEEK.h"
#include "KnowledgePosition.h"
#include "NPC.h"

CSteeringBehaviorKinematicSEEK::CSteeringBehaviorKinematicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target)
	: CSteeringBehavior(user, NpcAIMode::KinematicSeek)
	, m_pKnowledgePosition(target)
{
}

CSteeringBehaviorKinematicSEEK::~CSteeringBehaviorKinematicSEEK()
{
}

SSteeringForce CSteeringBehaviorKinematicSEEK::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// Rotation zum Spieler
	CHVector vToPlayer = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();
	resForce.fRotationForce = AngleVektoriaToZX(vToPlayer);
	resForce.Flags.bApplyRotationForce = false;

	// Laufe mit max. Geschwindigkeit in die Richtung
	// wird durch CSteeringBehavior::Update nach fRotationForce verrechnet
	// muss lediglich Länge übergeben
	resForce.Flags.bMoveByRot = true;
	resForce.vMovementForce = CHVector(m_pUser->GetKinematics().GetMaxMovementForce(), 0.0f, 0.0f);

	return resForce;
}
