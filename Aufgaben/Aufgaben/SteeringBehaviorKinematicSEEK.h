#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorKinematicSEEK : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicSEEK(CKnowledgePosition* pKnowledge);
	~CSteeringBehaviorKinematicSEEK();

public:
	CHVector GetForce() override;

private:
	CKnowledgePosition* m_pKnowledge;
};
