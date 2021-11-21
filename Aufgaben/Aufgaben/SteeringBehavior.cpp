#include "pch.h"
#include "SteeringBehavior.h"
#include "Npc.h"

CSteeringBehavior::CSteeringBehavior(CNpc* user, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: CAction(user, npcAiMode)
{
}

CSteeringBehavior::~CSteeringBehavior()
{
}

void CSteeringBehavior::Update(float fTime, float fTimeDelta)
{
	SSteeringForce force = GetForce();

	// bewegung
	m_pUser->GetKinematics().ApplyMovementForce(force.vMovementForce * fTimeDelta);

	// ausrichtung / rotation
	m_pUser->GetKinematics().ChangeOrientation(force.fRotationForce /** fTimeDelta*/);
}
