#pragma once

#include "SteeringBehavior.h"
#include "NormalDistribution.h"

class CKnowledgeWorldBorder;
class CSteeringBehaviorDynamicWANDER : public CSteeringBehavior
{
public:
	CSteeringBehaviorDynamicWANDER(CNpc* user, std::shared_ptr<CKnowledgeWorldBorder> pWorldBorder, float fOffset = 10.0f, float fRadius = 3.0f, float fMaxAngleChange = UM_DEG2RAD(1000));
	~CSteeringBehaviorDynamicWANDER();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgeWorldBorder> m_pWorldBorder;
	float m_fOffset;
	float m_fRadius;
	float m_fMaxAngleChange;

	float m_fCurAngle;
	static CNormalDistribution ms_Rnd;
};
