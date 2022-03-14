#pragma once

#include "SteeringBehavior.h"

class CKnowledgeWorldCharacters;

class CSteeringBehaviorSEPARATION : public CSteeringBehavior
{
public:
	CSteeringBehaviorSEPARATION(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> characters, float fFOVAngleDiff = QUARTERPI, float fFOVMaxDistance = 10.0f);
	~CSteeringBehaviorSEPARATION();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgeWorldCharacters> m_Characters;
	float m_fFOVAngleDiff;
	float m_fFOVMaxDistance;
};

