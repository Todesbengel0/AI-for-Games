#include "pch.h"
#include "SteeringBehaviorVELOCITY_MATCHING.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorVELOCITY_MATCHING::CSteeringBehaviorVELOCITY_MATCHING(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, float fActivationDistance /*= 15.0f*/)
	: CSteeringBehavior(user, NpcAIMode::VelocityMatching)
	, m_Buddies(buddies)
	, m_fActivationDistance(fActivationDistance)
{
}

CSteeringBehaviorVELOCITY_MATCHING::~CSteeringBehaviorVELOCITY_MATCHING()
{
}

SSteeringForce CSteeringBehaviorVELOCITY_MATCHING::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;
	resForce.BoundsFix = MoveBoundsFix::Bounce;
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	if (!m_Buddies)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	const CKnowledgeWorldCharacters::character_vec_t& buddies = m_Buddies->GetCharacters();
	if (buddies.size() <= 1)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	CHVector vAverageVelocity(0.0f, 0.0f, 0.0f, 0.0f); // muss W=0 initialisiert werden!
	int buddyCount = 0;
	float fAccumulatedSpeed = 0.0f;
	for (auto buddy : buddies)
	{
		if (buddy == m_pUser)
			continue;

		// NPC zum Ziel
		CHVector vToTarget = buddy->GetKinematics().GetPosition() - m_pUser->GetKinematics().GetPosition();
		float fDist = vToTarget.Length();

		if (fDist < m_fActivationDistance)
		{
			vAverageVelocity += buddy->GetKinematics().GetMovementForce();
			fAccumulatedSpeed += buddy->GetKinematics().GetMovementForce().Length();
			++buddyCount;
		}
	}

	// Wenn keiner in der N�he: Weiterlaufen wie zuvor (Vielleicht kann man auch Wander einf�gen?) !!Macht irgendwie Probleme am Rand des Feldes
	if (buddyCount == 0)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	// Mitteln der Bewegungen (wenn Summe der Bewegungen nicht Nullvektor)
	if (buddyCount > 1 && vAverageVelocity.Length() > 0.01f)
		ScaleVectorTo(vAverageVelocity, fAccumulatedSpeed / (float)buddyCount);

	resForce.vMovementForce = vAverageVelocity + vPreviousMovementForce;
	if (resForce.vMovementForce.Length() < 0.01f)	// passiert eig. nur, wenn NPCs re-spawned werden
		return resForce;

	ScaleVectorTo(resForce.vMovementForce, m_pUser->GetKinematics().GetMaxMovementForce());

	// �berpr�fung, ob es zu einer Beschleunigung kommt -> Anwenden der Beschleunigungsregulationen

 	SmoothForceDelta(resForce.vMovementForce, m_pUser->GetKinematics(), fTimeDelta);
 	LimitToRotation(resForce.vMovementForce
 		, AngleDiffToPreviousForce(resForce.vMovementForce)
		, m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);
	
	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
