#include "pch.h"
#include "SteeringBehaviorDynamicWANDER.h"
#include "Npc.h"
#include "KnowledgeWorldBorder.h"

#define EPSENV(x)	0.97f * (float)x

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

SSteeringForce CSteeringBehaviorDynamicWANDER::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

	// 
	CHVector vCircleCenter = m_pUser->GetKinematics().GetOrientationVec() * m_fOffset;

	float fNewAngle = ms_Rnd.RandFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange * fTimeDelta;

	// angle to vec !!MUSS HIER SCHON Z-ACHSE INVERTIERT WERDEN?
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	CHVector vTargetDir = vCircleCenter + vAngleDir * m_fRadius;
	vTargetDir.Norm();

	// NPC has Borderline-Syndrom
	//if (std::abs(m_pUser->GetKinematics().GetPosition().x) >= EPSENV(m_pWorldBorder->GetBoardSize().x))
	//	resForce.vMovementForce.x = -resForce.vMovementForce.x;
	//if (std::abs(m_pUser->GetKinematics().GetPosition().z) >= EPSENV(m_pWorldBorder->GetBoardSize().z))
	//	resForce.vMovementForce.z = -resForce.vMovementForce.z;

	resForce.vMovementForce = vTargetDir * m_pUser->GetKinematics().GetMaxMovementForce();

	// für korrekten Winkel muss Z-Achse invertiert werden (Brummkreisel!!)
	CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();

	static CNpc* trackNpc = m_pUser;
	if (trackNpc == m_pUser)
	{
		ULInfo("[%f,%f,%f] , %f , [%f,%f,%f] , [%f,%f,%f]"
			, vCircleCenter.x, vCircleCenter.y, vCircleCenter.z
			, m_fCurAngle
			, vAngleDir.x, vAngleDir.y, vAngleDir.z
			, vTargetDir.x, vTargetDir.y, vTargetDir.z
		);
	}

	return resForce;
}
