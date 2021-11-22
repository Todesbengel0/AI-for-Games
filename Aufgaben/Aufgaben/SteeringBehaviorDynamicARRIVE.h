#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorDynamicARRIVE : public CSteeringBehavior
{
public:
	CSteeringBehaviorDynamicARRIVE(CNpc* user, std::shared_ptr<CKnowledgePosition> target, float fBrakeRadius = 10.0f, float fBrakeFactor = 0.5f);
	~CSteeringBehaviorDynamicARRIVE();

public:
	SSteeringForce GetForce() override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
	float m_fBrakeRadius;
	float m_fBrakeFactor;
};
