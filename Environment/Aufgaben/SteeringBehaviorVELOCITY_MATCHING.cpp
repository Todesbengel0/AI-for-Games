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
	resForce.Flags.BoundsFix = MoveBoundsFix::Bounce;
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	if (!m_Buddies)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	// Neue Variante
	const CKnowledgeWorldCharacters::character_vec_t buddies = m_Buddies->GetCharactersNear(m_pUser, m_fActivationDistance);
	if (buddies.size() == 0)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	// AverageVelocity ist der Vektor, mit dem der NPC sich gerne bewegen würde, um der Gruppe zu folgen
	CHVector vAverageVelocity(0.0f, 0.0f, 0.0f, 0.0f); // muss W=0 initialisiert werden!
	float fAccumulatedSpeed = 0.0f;
	for (auto buddy : buddies)
	{
		vAverageVelocity += buddy->GetKinematics().GetMovementForce();
		fAccumulatedSpeed += buddy->GetKinematics().GetMovementForce().Length();
	}
	// Mitteln der Bewegungen (wenn Summe der Bewegungen nicht Nullvektor)
	if (buddies.size() > 1 && vAverageVelocity.Length() > 0.01f)
		ScaleVectorTo(vAverageVelocity, fAccumulatedSpeed / (float)buddies.size());

	resForce.vMovementForce = vAverageVelocity + vPreviousMovementForce;
	if (resForce.vMovementForce.Length() < 0.01f)	// passiert eig. nur, wenn NPCs re-spawned werden
		return resForce;

	// ScaleVectorTo(resForce.vMovementForce, m_pUser->GetKinematics().GetMaxMovementForce());
	ScaleVectorTo(resForce.vMovementForce, (vAverageVelocity.Length() + vPreviousMovementForce.Length()) * 0.5f);

	// Überprüfung, ob es zu einer Beschleunigung kommt -> Anwenden der Beschleunigungsregulationen

 	SmoothForceDelta(resForce.vMovementForce, m_pUser->GetKinematics(), fTimeDelta);
 	LimitToRotation(resForce.vMovementForce
 		, AngleDiffToPreviousForce(resForce.vMovementForce)
		, m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);
	
	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
