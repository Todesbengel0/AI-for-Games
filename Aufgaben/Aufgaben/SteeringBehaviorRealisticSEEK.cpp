#include "pch.h"
#include "SteeringBehaviorRealisticSEEK.h"
#include "Npc.h"
#include "KnowledgesInclude.h"

CSteeringBehaviorRealisticSEEK::CSteeringBehaviorRealisticSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target, const float breakFactor /*= 0.6f*/, const float minMovementVelocity /*= 1.0f*/)
	: CSteeringBehavior(user, NpcAIMode::DynamicSeek)
	, m_pKnowledgePosition(target)
	, m_fBreakFactor(breakFactor)
	, m_fMinMovementVelocity(minMovementVelocity)
{
}

CSteeringBehaviorRealisticSEEK::~CSteeringBehaviorRealisticSEEK()
{
}

SSteeringForce CSteeringBehaviorRealisticSEEK::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;
	resForce.bApplyRotationForce = false;
	resForce.bMoveByRot = false;

	if (!m_pKnowledgePosition)
		return resForce;

	// Bewegung, die der Boid gerne ausüben würde (Zum Ziel)
	CHVector vTargetedMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();
	Limit(vTargetedMovementForce, 0, m_pUser->GetKinematics().GetMaxMovementForce());

	// mitteln mit alter Kraft
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce = vTargetedMovementForce + vPreviousMovementForce;
	resForce.vMovementForce /= resForce.vMovementForce.Length();
	resForce.vMovementForce *= (vTargetedMovementForce.Length() + vPreviousMovementForce.Length()) * 0.5f;

	SmoothForceDelta(resForce.vMovementForce, m_pUser->GetKinematics(), fTimeDelta);

	LimitToRotation(resForce.vMovementForce
		, AngleDiffToPreviousForce(resForce.vMovementForce)
		, m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);

	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);
	return resForce;
}
