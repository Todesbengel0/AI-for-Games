#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorRealisticSEEK : public CSteeringBehavior
{
public:
	CSteeringBehaviorRealisticSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target, const float breakFactor = 0.6f, const float minMovementVelocity = 1.0f);
	~CSteeringBehaviorRealisticSEEK();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
	const float m_fBreakFactor;
	const float m_fMinMovementVelocity;
};

