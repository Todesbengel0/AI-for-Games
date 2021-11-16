#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorKinematicFLEE : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicFLEE(CKnowledgePosition* pKnowledge);
	~CSteeringBehaviorKinematicFLEE();

public:
	CHVector GetForce() override;

private:
	CKnowledgePosition* m_pKnowledgePosition;
};
