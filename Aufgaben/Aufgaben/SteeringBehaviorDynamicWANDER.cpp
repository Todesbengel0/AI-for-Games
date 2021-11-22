#include "pch.h"
#include "SteeringBehaviorDynamicWANDER.h"
#include "Npc.h"

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
	SSteeringForce res;

	// 
	CHVector vCircleCenter = m_pUser->GetKinematics().GetOrientationVec() * m_fOffset;

	float fNewAngle = ms_Rnd.RandFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange;

	// angle to vec
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	CHVector vTargetDir = vCircleCenter + vAngleDir * m_fRadius;
	vTargetDir.Norm();

	res.vMovementForce = vTargetDir * m_pUser->GetKinematics().GetMaxMovementForce();

	return res;
}
