#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;

class CSteeringBehaviorKinematicFLEE : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicFLEE(CNpc* user);
	~CSteeringBehaviorKinematicFLEE();

public:
	CHVector GetForce() override;
	void SetKnowledgePosition(CKnowledgePosition* target);

private:
	CKnowledgePosition* m_pKnowledgePosition;
};
