#pragma once

#include "SteeringBehavior.h"

class CKnowledgeWorldCharacters;

class CSteeringBehaviorVELOCITY_MATCHING : public CSteeringBehavior
{
public:
	CSteeringBehaviorVELOCITY_MATCHING(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, float fActivationDistance = 20.0f);
	~CSteeringBehaviorVELOCITY_MATCHING();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgeWorldCharacters> m_Buddies;
	float m_fActivationDistance;
};
