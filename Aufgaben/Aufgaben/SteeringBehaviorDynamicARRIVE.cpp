#include "pch.h"
#include "SteeringBehaviorDynamicARRIVE.h"
#include "Npc.h"
#include "KnowledgesInclude.h"

CSteeringBehaviorDynamicARRIVE::CSteeringBehaviorDynamicARRIVE(CNpc* user, std::shared_ptr<CKnowledgePosition> target, float fBrakeRadius /*= 10.0f*/, float fBrakeFactor /*= 0.25f*/)
	: CSteeringBehavior(user, NpcAIMode::DynamicArrive)
	, m_pKnowledgePosition(target)
	, m_fBrakeRadius(fBrakeRadius)
	, m_fBrakeFactor(fBrakeFactor)
{
}

CSteeringBehaviorDynamicARRIVE::~CSteeringBehaviorDynamicARRIVE()
{
}

SSteeringForce CSteeringBehaviorDynamicARRIVE::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// bewegung zum ziel
	resForce.vMovementForce = m_pKnowledgePosition->GetPosition() - m_pUser->GetKinematics().GetPosition();

	float fBrake = resForce.vMovementForce.Length() / m_fBrakeRadius;

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vCurMovementForce;

	// schönere Mittlung mit /2 (kein ARRIVE notwendig), aber nicht gefragt
	//resForce.vMovementForce *= 0.5f;
	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// wenn im Radius, abbremsen
	if (fBrake < 1.0f)
		resForce.vMovementForce *= fBrake / m_fBrakeFactor;

	// für korrekten Winkel muss Z-Achse invertiert werden
	CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();

	return resForce;
}
