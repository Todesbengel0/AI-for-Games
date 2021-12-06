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
	// resultierende Kraft, wir übernehmen Rotationskraftauswirkung über Zeit (bApplyRotationForce = false)
	SSteeringForce resForce;
	resForce.bApplyRotationForce = false;
	resForce.BoundsFix = MoveBoundsFix::Bounce;

	// kinematische Daten des NPCs / Boids
	CHVector vUserPos = m_pUser->GetKinematics().GetPosition();
	CHVector vUserOri = m_pUser->GetKinematics().GetOrientationVec();
	float fAUserOri = m_pUser->GetKinematics().GetOrientationAngleZX();

	// Hilfskreis für Wander Bewegung
	CHVector vCircleCenter = vUserPos + vUserOri * m_fOffset;

	// Debug check Orientierung- und Winkelumrechnungen
#ifdef _DEBUG
	CHVector vToCircle = vCircleCenter - vUserPos;
	vToCircle /= vToCircle.Length();
	assert((vUserOri - vToCircle).Length() < 0.001f);	// Kreis muss in Laufbahn des Boids liegen
	float fAToCircle = AngleVektoriaToZX(vToCircle);
	assert(std::abs(fAToCircle - fAUserOri) < 0.001f);	// Umrechnung zu Skalarwinkel muss auch übereinstimmen
#endif // _DEBUG

	// fortlaufender Winkel im Kreis
	float fNewAngle = ms_Rnd.RandNormFt();
	m_fCurAngle += fNewAngle * m_fMaxAngleChange * fTimeDelta;

	// lokaler Winkelvektor im Kreis (in Standardorientierung nach +X)
	CHVector vAngleDir(std::cosf(m_fCurAngle), 0.0f, std::sinf(m_fCurAngle));

	// Punkt auf Kreisbahn
	CHVector vCirclePoint = vCircleCenter + vAngleDir * m_fRadius;

	// Richtung: Boid zu Punkt
	CHVector vDir = vCirclePoint - vUserPos;
	vDir /= vDir.Length();
	float fDir = AngleVektoriaToZX(vDir);	// Skalarwinkel in lokalem Kreis

	// Rotationskraftänderung
	// Addition von Winkeldelta (zu altem Winkel) verrechnet mit Zeitdelta
	resForce.fRotationForce = fAUserOri + AngleDiff(fAUserOri, fDir) * fTimeDelta;

	// Laufe mit max. Geschwindigkeit in neue Richtung
	// wird durch CSteeringBehavior::Update nach fRotationForce verrechnet
	// muss lediglich Länge übergeben
	resForce.bMoveByRot = true;
	resForce.vMovementForce = CHVector(m_pUser->GetKinematics().GetMaxMovementForce(), 0.0f, 0.0f);

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
