#include "pch.h"
#include "SteeringBehaviorDynamicWANDER.h"
#include "Npc.h"
#include "KnowledgeWorldBorder.h"

#define EPSENV(x)	0.97f * (float)x

CNormalDistribution CSteeringBehaviorDynamicWANDER::ms_Rnd;

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

	CHVector vUserPos = m_pUser->GetKinematics().GetPosition();
	CHVector vUserOri = m_pUser->GetKinematics().GetOrientationVec();
	float fAUserOri = m_pUser->GetKinematics().GetOrientationAngleXZ();

	// Hilfskreis für Wander Bewegung
	CHVector vCircleCenter = vUserPos + vUserOri * m_fOffset;

	// Debug check Orientierung- und Winkelumrechnungen
#ifdef _DEBUG
	CHVector vToCircle = vCircleCenter - vUserPos;
	vToCircle.Norm();
	assert((vUserOri - vToCircle).Length() < 0.001f);
	float fA1 = CKinematics::AngleVektoriaToXZ(vToCircle);
	assert(std::abs(fA1 - fAUserOri) < 0.001f);
#endif // _DEBUG


	float fNewAngle = ms_Rnd.RandNormFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange * fTimeDelta;

	// Winkel bezüglich -Z-Achse
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	CHVector vCirclePoint = vCircleCenter + vAngleDir * m_fRadius;

	CHVector vDir = vCirclePoint - vUserPos;
	vDir.Norm();
	float fDir = CKinematics::AngleVektoriaToXZ(vDir);

	// NPC has Borderline-Syndrom
	//if (std::abs(m_pUser->GetKinematics().GetPosition().x) >= EPSENV(m_pWorldBorder->GetBoardSize().x))
	//	resForce.vMovementForce.x = -resForce.vMovementForce.x;
	//if (std::abs(m_pUser->GetKinematics().GetPosition().z) >= EPSENV(m_pWorldBorder->GetBoardSize().z))
	//	resForce.vMovementForce.z = -resForce.vMovementForce.z;

	//resForce.vMovementForce = CHVector(0.0f, 0.0f, -1.0f) * m_pUser->GetKinematics().GetMaxMovementForce();

	// Skalarwinkel des Kraftvektors
	//resForce.fRotationForce = m_fCurAngle;
	resForce.fRotationForce = fAUserOri + CKinematics::AngleDiff(fAUserOri, fDir) * fTimeDelta;
	//resForce.fRotationForce = CKinematics::AngleDiff(fDir, m_pUser->GetKinematics().GetOrientationAngle());
	//resForce.fRotationForce = GetAngleDirectionByZAxis(vDir);
	//resForce.fRotationForce = m_pUser->GetKinematics().GetOrientationVec().Angle(vDir);
	resForce.bApplyRotationForce = false;
	//resForce.bMoveByRot = true;

	// Debug logging
//#ifdef _DEBUG
//	static CNpc* trackNpc = m_pUser;
//	if (trackNpc == m_pUser)
//	{
//		ULInfo("Pos[%.1f,%.1f,%.1f] , Ori[%.3f,%.3f,%.3f] => Angle[%f] , CircleCenter[%.1f,%.1f,%.1f] , CirclePoint[%.1f,%.1f,%.1f] , NewOri[%.3f,%.3f,%.3f] %f"
//			, vUserPos.x, vUserPos.y, vUserPos.z
//			, vUserOri.x, vUserOri.y, vUserOri.z
//			, m_fCurAngle
//			, vCircleCenter.x, vCircleCenter.y, vCircleCenter.z
//			, vCirclePoint.x, vCirclePoint.y, vCirclePoint.z
//			, vDir.x, vDir.y, vDir.z
//			, resForce.fRotationForce
//		);
//	}
//#endif // _DEBUG

	return resForce;
}
