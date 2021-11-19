#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CSteeringBehaviorKinematicSEEK : public CSteeringBehavior
{
public:
	CSteeringBehaviorKinematicSEEK(CNpc* user);
	~CSteeringBehaviorKinematicSEEK();

public:
	CHVector GetForce() override;
	void SetKnowledgePosition(CKnowledgePosition* target);

private:
	CKnowledgePosition* m_pKnowledge;
};
