#include "pch.h"
#include "SteeringBehaviorCOHESION.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorCOHESION::CSteeringBehaviorCOHESION(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, float fActivationDistance /*= 20.0f*/)
	: CSteeringBehavior(user, NpcAIMode::Cohesion)
	, m_Buddies(buddies)
	, m_fActivationDistance(fActivationDistance)
{
}

CSteeringBehaviorCOHESION::~CSteeringBehaviorCOHESION()
{
}

SSteeringForce CSteeringBehaviorCOHESION::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;
	resForce.Flags.BoundsFix = MoveBoundsFix::Bounce;
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	if (!m_Buddies)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	const CKnowledgeWorldCharacters::character_vec_t buddies = m_Buddies->GetCharactersNear(m_pUser, m_fActivationDistance);
	if (buddies.size() == 0)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	// AverageVelocity ist der Vektor, mit dem der NPC sich gerne bewegen würde, um der Gruppe zu folgen
	CHVector vCenterOfCharacters(0.0f, 0.0f, 0.0f, 0.0f); // W=0, da zwar Ortsvektor, aber noch nullptr (sozusagen)!
	for (auto buddy : buddies)
	{
		vCenterOfCharacters += buddy->GetKinematics().GetPosition();
	}
	// Mitteln der Bewegungen (wenn Summe der Bewegungen nicht Nullvektor)
	if (buddies.size() > 1)
		vCenterOfCharacters /= float(buddies.size());

	// DirToCenter ist der Vektor, mit dem der NPC sich gerne bewegen würde
	CHVector vDirToCenter = vCenterOfCharacters - m_pUser->GetKinematics().GetPosition();
	float force = m_pUser->GetKinematics().GetMaxMovementForce() * vDirToCenter.Length() / m_fActivationDistance;
	ScaleVectorTo(vDirToCenter, force);

	resForce.vMovementForce = vDirToCenter;
	if (resForce.vMovementForce.Length() < 0.01f)	// passiert eig. nur, wenn NPCs re-spawned werden
		return resForce;

	// Überprüfung, ob es zu einer Beschleunigung kommt -> Anwenden der Beschleunigungsregulationen
	SmoothForceDelta(resForce.vMovementForce, m_pUser->GetKinematics(), fTimeDelta);
	LimitToRotation(resForce.vMovementForce
		, AngleDiffToPreviousForce(resForce.vMovementForce)
		, m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);

	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
