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
	SSteeringForce force = GetForce(fTimeDelta);

	// bewegung
	Limit(force.vMovementForce, m_pUser->GetKinematics().GetMaxMovementForce());
	m_pUser->GetKinematics().ApplyMovementForce(force.vMovementForce, fTimeDelta);

	// ausrichtung / rotation
	m_pUser->GetKinematics().ChangeOrientation(force.fRotationForce /** fTimeDelta*/);
}

void CSteeringBehavior::Limit(CHVector& v, float maxLength)
{
	if (v.Length() <= maxLength)
		return;

	v.Norm();
	v *= maxLength;
}
