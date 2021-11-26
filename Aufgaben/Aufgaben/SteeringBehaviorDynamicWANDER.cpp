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

	// Hilfskreis für Wander Bewegung
	CHVector vCircleCenter = m_pUser->GetKinematics().GetPosition() + m_pUser->GetKinematics().GetOrientationVec() * m_fOffset;

	float fNewAngle = ms_Rnd.RandFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange * fTimeDelta;

	// angle to vec !!MUSS HIER SCHON Z-ACHSE INVERTIERT WERDEN?
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	CHVector vCirclePoint = vCircleCenter + vAngleDir * m_fRadius;

	CHVector vDir = vCirclePoint - m_pUser->GetKinematics().GetPosition();
	vDir.Norm();

	// NPC has Borderline-Syndrom
	//if (std::abs(m_pUser->GetKinematics().GetPosition().x) >= EPSENV(m_pWorldBorder->GetBoardSize().x))
	//	resForce.vMovementForce.x = -resForce.vMovementForce.x;
	//if (std::abs(m_pUser->GetKinematics().GetPosition().z) >= EPSENV(m_pWorldBorder->GetBoardSize().z))
	//	resForce.vMovementForce.z = -resForce.vMovementForce.z;

	resForce.vMovementForce = vDir * m_pUser->GetKinematics().GetMaxMovementForce();

	// Skalarwinkel des Kraftvektors
	//resForce.fRotationForce = GetAngleDirectionByZAxis(vDir);
	resForce.fRotationForce = m_pUser->GetKinematics().GetOrientationVec().Angle(vDir);
	//resForce.bApplyRotationForce = false;

	static CNpc* trackNpc = m_pUser;
	if (trackNpc == m_pUser)
	{
		ULInfo("Pos[%.1f,%.1f,%.1f] , Ori[%.3f,%.3f,%.3f] => Angle[%f] , CircleCenter[%.1f,%.1f,%.1f] , CirclePoint[%.1f,%.1f,%.1f] , NewOri[%.3f,%.3f,%.3f] %f"
			, m_pUser->GetKinematics().GetPosition().x, m_pUser->GetKinematics().GetPosition().y, m_pUser->GetKinematics().GetPosition().z
			, m_pUser->GetKinematics().GetOrientationVec().x, m_pUser->GetKinematics().GetOrientationVec().y, m_pUser->GetKinematics().GetOrientationVec().z
			, m_fCurAngle
			, vCircleCenter.x, vCircleCenter.y, vCircleCenter.z
			, vCirclePoint.x, vCirclePoint.y, vCirclePoint.z
			, vDir.x, vDir.y, vDir.z
			, resForce.fRotationForce
		);
	}

	return resForce;
}
