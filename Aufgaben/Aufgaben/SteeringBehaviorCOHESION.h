#pragma once

#include "SteeringBehavior.h"

class CKnowledgeWorldCharacters;

class CSteeringBehaviorCOHESION : public CSteeringBehavior
{
public:
	CSteeringBehaviorCOHESION(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, float fActivationDistance = 20.0f);
	~CSteeringBehaviorCOHESION();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgeWorldCharacters> m_Buddies;
	float m_fActivationDistance;
};
