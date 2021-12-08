#include "pch.h"
#include "SteeringBehaviorSEPARATION.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorSEPARATION::CSteeringBehaviorSEPARATION(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> characters, float fFOVAngleDiff /*= QUARTERPI*/, float fFOVMaxDistance /*= 25.0f*/)
	: CSteeringBehavior(user, NpcAIMode::Seperation)
	, m_Characters(characters)
	, m_fFOVAngleDiff(fFOVAngleDiff)
	, m_fFOVMaxDistance(fFOVMaxDistance)
{
}

CSteeringBehaviorSEPARATION::~CSteeringBehaviorSEPARATION()
{
}

SSteeringForce CSteeringBehaviorSEPARATION::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;
	resForce.BoundsFix = MoveBoundsFix::Bounce;
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();

	if (!m_Characters)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	const CKnowledgeWorldCharacters::character_vec_t characters = m_Characters->GetCharactersInFOV(m_pUser, m_fFOVAngleDiff, m_fFOVMaxDistance);
	if (characters.size() == 0)
	{
		resForce.vMovementForce = vPreviousMovementForce;
		resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
		return resForce;
	}

	// EvasionVelocity ist der Vektor, mit dem der NPC abbremsen möchte, um anderen Objekten auszuweichen
	CHVector vEvasionVelocity(0.0f, 0.0f, 0.0f, 0.0f); // muss W=0 initialisiert werden!
	float fAccumulatedBreakFactor = 0.0f;
	for (auto character : characters)
	{
		CHVector vTargetToUser = m_pUser->GetKinematics().GetPosition() - character->GetKinematics().GetPosition();
		float distance = vTargetToUser.Length();
		float force = vPreviousMovementForce.Length() * (m_fFOVMaxDistance - distance) / m_fFOVMaxDistance;
		fAccumulatedBreakFactor += force;
		vEvasionVelocity += ScaleVectorTo(vTargetToUser, force);
	}
	// Mitteln der Break-Faktoren
	if (characters.size() > 1 && vEvasionVelocity.Length() > 0.01f)
		ScaleVectorTo(vEvasionVelocity, fAccumulatedBreakFactor / (float)characters.size());

	resForce.vMovementForce = vEvasionVelocity + vPreviousMovementForce;
	if (resForce.vMovementForce.Length() < 0.01f)	// passiert eig. nur, wenn NPCs re-spawned werden
		return resForce;

	SmoothForceDelta(resForce.vMovementForce, m_pUser->GetKinematics(), fTimeDelta);
	LimitToRotation(resForce.vMovementForce
		, AngleDiffToPreviousForce(resForce.vMovementForce)
		, m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);

	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
	return resForce;
}
