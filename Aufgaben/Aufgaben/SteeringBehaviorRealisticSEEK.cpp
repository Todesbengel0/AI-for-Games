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

	// bewegung zum ziel
	resForce.vMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();

	// mitteln mit alter Kraft
	CHVector vPreviousMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vPreviousMovementForce;

	/*schönere Mittlung mit breakFactor (ersetzt ARRIVE)
		resForce.vMovementForce *= m_fBreakFactor;*/
	BreakThrottle(resForce.vMovementForce, fTimeDelta);

	float fTemp = 0.0f;
	// Bei Beschleunigung den Regulierungen folgen
	if (resForce.vMovementForce.Length() > vPreviousMovementForce.Length())
		AccelerationThrottle(resForce.vMovementForce, fTimeDelta);
		


	// Drehgeschwindigkeit drosseln
	/*
	float fAngleDifference = AngleDiff(AngleVektoriaToZX(resForce.vMovementForce), m_pUser->GetKinematics().GetOrientationAngleZX());
	fTemp = 0.0f;
	if (abs(fAngleDifference) > (fTemp = (m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta)))
	{
		// Kürzesten Winkel zum Ziel nehmen
		float fAlpha = fAngleDifference - fTemp;
		if (abs(fAngleDifference + fTemp) < abs(fAngleDifference - fTemp))
			fAlpha = fAngleDifference + fTemp;

		// Force-Vector drehen
		CHMat mYRotMat = CHMat(std::cosf(fAlpha), 0, sinf(fAlpha), 0, 0, 1, 0, 0, -sinf(fAlpha), 0, cosf(fAlpha), 0, 0, 0, 0, 1);
		resForce.vMovementForce = mYRotMat * resForce.vMovementForce;
	}*/
	LimitToRotation(resForce.vMovementForce
					,AngleDiffToPreviousForce(resForce.vMovementForce)
					,m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta);

	resForce.fRotationForce = AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
