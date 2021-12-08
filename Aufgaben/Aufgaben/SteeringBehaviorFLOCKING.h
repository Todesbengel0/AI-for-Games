#pragma once

#include "SteeringBehaviorBLEND.h"
#include "SteeringBehaviorCOHESION.h"
#include "SteeringBehaviorSEPARATION.h"
#include "SteeringBehaviorVELOCITY_MATCHING.h"

class CSteeringBehaviorFLOCKING : public CSteeringBehaviorBLEND
{
public:
	CSteeringBehaviorFLOCKING(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, std::shared_ptr<CKnowledgeWorldCharacters> characters, float fVelocityMatchingWeight = 1.0f, float fCohesionWeight = 1.0f, float fSeperationWeight = 1.0f, float fVelocityMatchingDistance = 15.0f, float fCohesionDistance = 20.0f, float fSeperationFOVAngle = QUARTERPI, float fSeparationFOVDistance = 10.0f);
	~CSteeringBehaviorFLOCKING();

public:
	SSteeringForce GetForce(float fTimeDelta) override;

private:
	std::shared_ptr<CKnowledgeWorldCharacters> m_Buddies;
	std::shared_ptr<CKnowledgeWorldCharacters> m_Characters;
	float m_fVelocityMatchingWeight;
	float m_fCohesionWeight;
	float m_fSeparationWeight;
	float m_fVelocityMatchingDistance;
	float m_fCohesionDistance;
	float m_fSeparationFOVAngle;
	float m_fSeparationFOVDistance;
	std::shared_ptr<CSteeringBehaviorCOHESION> m_Cohesion;
	std::shared_ptr<CSteeringBehaviorVELOCITY_MATCHING> m_VelocityMatching;
	std::shared_ptr<CSteeringBehaviorSEPARATION> m_Separation;
};
