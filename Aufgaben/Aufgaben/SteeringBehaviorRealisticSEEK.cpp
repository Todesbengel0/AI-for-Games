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
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vCurMovementForce;

	// schönere Mittlung mit breakFactor (ersetzt ARRIVE)
	resForce.vMovementForce *= m_fBreakFactor;

	float fTemp = 0.0f;
	// setzt Geschwindigkeit mindestens auf MinMovementVelocity
	if (vCurMovementForce.Length() < m_fMinMovementVelocity && vCurMovementForce.Length() < resForce.vMovementForce.Length())
	{
		resForce.vMovementForce.Norm();
		resForce.vMovementForce *= m_fMinMovementVelocity;
	}
	// Beschleunigung soll nicht zu extrem sein
	else if (resForce.vMovementForce.Length() > (fTemp = (vCurMovementForce.Length() + (m_pUser->GetKinematics().GetMaxMovementAcceleration() - 1) * fTimeDelta)))
	{
		resForce.vMovementForce.Norm();
		resForce.vMovementForce *= fTemp;
	}

	//// für korrekten Winkel muss Z-Achse invertiert werden
	//CHVector vFixedDir = resForce.vMovementForce;
	//vFixedDir.z = -vFixedDir.z;
	//
	//// Drehgeschwindigkeit drosseln
	//float fRotationAngle =  m_pUser->GetKinematics().GetOrientationAngleZX() - vFixedDir.AngleXZ();
	//fTemp = 0.0f;
	//if (abs(fRotationAngle) > (fTemp = (m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta)) && resForce.vMovementForce.Length() > vCurMovementForce.Length())
	//{
	//	if (fRotationAngle > PI)
	//		fRotationAngle -= TWOPI;
	//	else if (fRotationAngle < -PI)
	//		fRotationAngle += TWOPI;
	//
	//	// Kürzesten Winkel zum Ziel nehmen
	//	float fAlpha = fRotationAngle - fTemp;
	//	if (abs(fRotationAngle + fTemp) < abs(fRotationAngle - fTemp))
	//		fAlpha = fRotationAngle + fTemp;
	//	
	//	// Force-Vector drehen
	//	CHMat mYRotMat = CHMat(std::cosf(fAlpha), 0, sinf(fAlpha), 0, 0, 1, 0, 0, -sinf(fAlpha), 0, cosf(fAlpha), 0, 0, 0, 0, 1);
	//	resForce.vMovementForce = mYRotMat * resForce.vMovementForce;
	//
	//	// Direction übergeben
	//	vFixedDir = resForce.vMovementForce;
	//	vFixedDir.z = -vFixedDir.z;
	//}
	//
	//resForce.fRotationForce = vFixedDir.AngleXZ();

	// Drehgeschwindigkeit drosseln
	float fRotationAngle = CKinematics::AngleDiff(CKinematics::AngleVektoriaToZX(resForce.vMovementForce), m_pUser->GetKinematics().GetOrientationAngleZX());
	fTemp = 0.0f;
	if (abs(fRotationAngle) > (fTemp = (m_pUser->GetKinematics().GetMaxRotationForce() * fTimeDelta)) && resForce.vMovementForce.Length() > vCurMovementForce.Length())
	{
		// Kürzesten Winkel zum Ziel nehmen
		float fAlpha = fRotationAngle - fTemp;
		if (abs(fRotationAngle + fTemp) < abs(fRotationAngle - fTemp))
			fAlpha = fRotationAngle + fTemp;

		// Force-Vector drehen
		CHMat mYRotMat = CHMat(std::cosf(fAlpha), 0, sinf(fAlpha), 0, 0, 1, 0, 0, -sinf(fAlpha), 0, cosf(fAlpha), 0, 0, 0, 0, 1);
		resForce.vMovementForce = mYRotMat * resForce.vMovementForce;
	}

	resForce.fRotationForce = CKinematics::AngleVektoriaToZX(resForce.vMovementForce);

	return resForce;
}
