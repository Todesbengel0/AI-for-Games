#pragma once

#include "SteeringBehaviorBLEND.h"
#include "SteeringBehaviorCOHESION.h"
#include "SteeringBehaviorSEPARATION.h"
#include "SteeringBehaviorVELOCITY_MATCHING.h"

class CSteeringBehaviorFLOCKING : public CSteeringBehaviorBLEND
{
public:
	CSteeringBehaviorFLOCKING(CNpc* user
		, std::shared_ptr<CKnowledgeWorldCharacters> buddies
		, std::shared_ptr<CKnowledgeWorldCharacters> characters
		, float fVelocityMatchingWeight = 0.33f
		, float fCohesionWeight = 0.33f
		, float fSeperationWeight = 0.33f
		, float fVelocityMatchingDistance = 15.0f
		, float fCohesionDistance = 20.0f
		, float fSeperationFOVAngle = QUARTERPI
		, float fSeparationFOVDistance = 10.0f
	);
	~CSteeringBehaviorFLOCKING();
};
