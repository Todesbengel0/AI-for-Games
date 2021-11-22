#include "pch.h"
#include "SteeringBehaviorDynamicWANDER.h"
#include "Npc.h"
#include "KnowledgeWorldBorder.h"

#define EPSENV(x)	0.95f * (float)x

CRandom CSteeringBehaviorDynamicWANDER::ms_Rnd;

CSteeringBehaviorDynamicWANDER::CSteeringBehaviorDynamicWANDER(CNpc* user, std::shared_ptr<CKnowledgeWorldBorder> pWorldBorder, float fOffset, float fRadius, float fMaxAngleChange)
	: CSteeringBehavior(user, NpcAIMode::DynamicWander)
	, m_pWorldBorder(pWorldBorder)
	, m_fOffset(fOffset)
	, m_fRadius(fRadius)
	, m_fMaxAngleChange(fMaxAngleChange)
	, m_fCurAngle(0.0f)
{
}

CSteeringBehaviorDynamicWANDER::~CSteeringBehaviorDynamicWANDER()
{
}

SSteeringForce CSteeringBehaviorDynamicWANDER::GetForce()
{
	SSteeringForce resForce;

	// 
	CHVector vCircleCenter = m_pUser->GetKinematics().GetOrientationVec() * m_fOffset;

	float fNewAngle = ms_Rnd.RandFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange;

	// angle to vec
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	CHVector vTargetDir = vCircleCenter + vAngleDir * m_fRadius;
	vTargetDir.Norm();

	// NPC has Borderline-Syndrom
	if (std::abs(m_pUser->GetKinematics().GetPosition().x) >= EPSENV(m_pWorldBorder->GetBoardSize().x))
	{
		CHVector vXNorm = CHVector(1.0f, 0.0f, 0.0f);
		resForce.vMovementForce -= vXNorm * (resForce.vMovementForce * vXNorm) * 2;
	}
	if (std::abs(m_pUser->GetKinematics().GetPosition().z) >= EPSENV(m_pWorldBorder->GetBoardSize().z))
	{
		CHVector vZNorm = CHVector(0.0f, 0.0f, 1.0f);
		resForce.vMovementForce -= vZNorm * (resForce.vMovementForce * vZNorm) * 2;
	}

	resForce.vMovementForce = vTargetDir * m_pUser->GetKinematics().GetMaxMovementForce();

	// für korrekten Winkel muss Z-Achse invertiert werden (Brummkreisel!!)
	/*CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();*/

	return resForce;
}
