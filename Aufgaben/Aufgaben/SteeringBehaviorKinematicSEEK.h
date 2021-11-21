#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorKinematicSEEK : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicSEEK(CNpc* user, std::shared_ptr<CKnowledgePosition> target);
	~CSteeringBehaviorKinematicSEEK();

public:
	SSteeringForce GetForce() override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
};
