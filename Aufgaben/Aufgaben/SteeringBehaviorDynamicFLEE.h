#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorDynamicFLEE : public CSteeringBehavior
{
public:
	CSteeringBehaviorDynamicFLEE(CNpc* user, std::shared_ptr<CKnowledgePosition> target);
	~CSteeringBehaviorDynamicFLEE();

public:
	SSteeringForce GetForce() override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
};
