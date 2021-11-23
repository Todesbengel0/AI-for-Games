#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;

class CSteeringBehaviorKinematicFLEE : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicFLEE(CNpc* user, std::shared_ptr<CKnowledgePosition> target);
	~CSteeringBehaviorKinematicFLEE();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
};
