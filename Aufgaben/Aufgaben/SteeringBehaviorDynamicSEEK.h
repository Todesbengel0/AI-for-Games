#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorDynamicSEEK : public CSteeringBehavior
{
public:
	CSteeringBehaviorDynamicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target);
	~CSteeringBehaviorDynamicSEEK();

public:
	SSteeringForce GetForce() override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
};

