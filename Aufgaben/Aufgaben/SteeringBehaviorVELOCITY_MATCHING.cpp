#include "pch.h"
#include "SteeringBehaviorVELOCITY_MATCHING.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorVELOCITY_MATCHING::CSteeringBehaviorVELOCITY_MATCHING(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, float fActivationDistance /*= 6.0f*/)
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

	if (!m_Buddies)
		return resForce;

	const CKnowledgeWorldCharacters::character_vec_t& buddies = m_Buddies->GetCharacters();
	if (buddies.size() <= 1)
		return resForce;

	CHVector vAverageVelocity;
	int buddyCount = 0;
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
			++buddyCount;
		}
	}

	// Mitteln der Bewegungen
	if (buddyCount > 1)
		vAverageVelocity /= float(buddyCount);

	// Verrechnen mit vorheriger Kraft
	CHVector vLastMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce = vLastMovementForce + vAverageVelocity;

	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
