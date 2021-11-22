#include "pch.h"
#include "SteeringBehaviorDynamicESCAPE.h"
#include "KnowledgesInclude.h"
#include "Npc.h"

CSteeringBehaviorDynamicESCAPE::CSteeringBehaviorDynamicESCAPE(CNpc* user, std::shared_ptr<CKnowledgePosition> target, std::shared_ptr<CKnowledgeWorldBorder> worldBorder)
	: CSteeringBehavior(user, NpcAIMode::DynamicFlee)
	, m_pKnowledgePosition(target)
	, m_pWorldBorder(worldBorder)
{
}

CSteeringBehaviorDynamicESCAPE::~CSteeringBehaviorDynamicESCAPE()
{
}

SSteeringForce CSteeringBehaviorDynamicESCAPE::GetForce()
{
	SSteeringForce resForce;

	if (!m_pKnowledgePosition)
		return resForce;

	// bewegung zum ziel
	resForce.vMovementForce = m_pUser->GetKinematics().GetPosition() - m_pKnowledgePosition->GetPosition();

	// mitteln mit alter Kraft
	CHVector vCurMovementForce = m_pUser->GetKinematics().GetMovementForce();
	resForce.vMovementForce += vCurMovementForce;

	resForce.vMovementForce.Norm();
	resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();

	// Überprüfen, ob Zielpunkt außerhalb der Map liegen würde (an manchen Ecken gibts noch Vorzeichenfehler)
	CHVector vMovementPosition = m_pUser->GetKinematics().GetPosition() + resForce.vMovementForce;
	if (std::abs(vMovementPosition.x) > m_pWorldBorder->GetBoardSize().x && std::abs(vMovementPosition.z) > m_pWorldBorder->GetBoardSize().z)
	{
		CHVector vCornerPosition = CHVector((vMovementPosition.x / std::abs(vMovementPosition.x)) * m_pWorldBorder->GetBoardSize().x
											, 0.0f
											, (vMovementPosition.z / std::abs(vMovementPosition.z)) * m_pWorldBorder->GetBoardSize().z);
		CHVector vTestForce = resForce.vMovementForce;
		if (std::abs(vTestForce.x) > std::abs(vTestForce.z))
		{
			vTestForce.x = vTestForce.z;
			vTestForce.z = -vTestForce.x;
			CHVector vRotatedPosition = m_pUser->GetKinematics().GetPosition() + vTestForce;
			if (std::abs(vRotatedPosition.x) > m_pWorldBorder->GetBoardSize().x)
			{
				if (vRotatedPosition.x < 0.0f)
					vTestForce.x -= vRotatedPosition.x + m_pWorldBorder->GetBoardSize().x;
				else
					vTestForce.x -= vRotatedPosition.x - m_pWorldBorder->GetBoardSize().x;
				vRotatedPosition = m_pUser->GetKinematics().GetPosition() + vTestForce;
			}
			
			if ((vRotatedPosition - m_pKnowledgePosition->GetPosition()).Length() > (vCornerPosition - m_pKnowledgePosition->GetPosition()).Length())
			{
				resForce.vMovementForce = vTestForce;
				resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();
			}
		}
		else if (std::abs(vTestForce.x) < std::abs(vTestForce.z))
		{
			vTestForce.x = -vTestForce.z;
			vTestForce.z = vTestForce.x;
			CHVector vRotatedPosition = m_pUser->GetKinematics().GetPosition() + vTestForce;
			if (std::abs(vRotatedPosition.z) > m_pWorldBorder->GetBoardSize().z)
			{
				if (vRotatedPosition.z < 0.0f)
					vTestForce.z -= vRotatedPosition.z + m_pWorldBorder->GetBoardSize().z;
				else
					vTestForce.z -= vRotatedPosition.z - m_pWorldBorder->GetBoardSize().z;
				vRotatedPosition = m_pUser->GetKinematics().GetPosition() + vTestForce;
			}

			if ((vRotatedPosition - m_pKnowledgePosition->GetPosition()).Length() > (vCornerPosition - m_pKnowledgePosition->GetPosition()).Length())
			{
				resForce.vMovementForce = vTestForce;
				resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();
			}
		}
	}
	else if (std::abs(vMovementPosition.x) > m_pWorldBorder->GetBoardSize().x)
	{
		if (vMovementPosition.x < 0.0f)
			resForce.vMovementForce.x -= vMovementPosition.x + m_pWorldBorder->GetBoardSize().x;
		else
			resForce.vMovementForce.x -= vMovementPosition.x - m_pWorldBorder->GetBoardSize().x;
		resForce.vMovementForce.Norm();
		resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();
	}
	else if (std::abs(vMovementPosition.z) > m_pWorldBorder->GetBoardSize().z)
	{
		if (vMovementPosition.z < 0.0f)
			resForce.vMovementForce.z -= vMovementPosition.z + m_pWorldBorder->GetBoardSize().z;
		else
			resForce.vMovementForce.z -= vMovementPosition.z - m_pWorldBorder->GetBoardSize().z;
		resForce.vMovementForce.Norm();
		resForce.vMovementForce *= m_pUser->GetKinematics().GetMaxMovementForce();
	}

	// für korrekten Winkel muss Z-Achse invertiert werden
	CHVector vFixedDir = resForce.vMovementForce;
	vFixedDir.z = -vFixedDir.z;
	resForce.fRotationForce = vFixedDir.AngleXZ();

	return resForce;
}
