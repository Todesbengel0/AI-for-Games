#include "pch.h"
#include "SteeringBehaviorFLOCKING.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorFLOCKING::CSteeringBehaviorFLOCKING(CNpc* user
	, std::shared_ptr<CKnowledgeWorldCharacters> buddies
	, std::shared_ptr<CKnowledgeWorldCharacters> characters
	, float fVelocityMatchingWeight /*= 0.33f*/
	, float fCohesionWeight /*= 0.33f*/
	, float fSeperationWeight /*= 0.33f*/
	, float fVelocityMatchingDistance /*= 15.0f*/
	, float fCohesionDistance /*= 20.0f*/
	, float fSeperationFOVAngle /*= QUARTERPI*/
	, float fSeparationFOVDistance /*= 10.0f*/
)
	: CSteeringBehaviorBLEND(user, NpcAIMode::Flocking)
{
	AddBehavior({ std::make_shared<CSteeringBehaviorVELOCITY_MATCHING>(user, buddies, fVelocityMatchingDistance), fVelocityMatchingWeight });
	AddBehavior({ std::make_shared<CSteeringBehaviorSEPARATION>(user, characters, fSeperationFOVAngle, fSeparationFOVDistance), fSeperationWeight });
	AddBehavior({ std::make_shared<CSteeringBehaviorCOHESION>(user, buddies, fCohesionDistance), fCohesionWeight });

	SSteeringForceFlags steeringForceFlags;
	steeringForceFlags.bApplyRotationForce = false;
	steeringForceFlags.bMoveByRot = false;
	steeringForceFlags.BoundsFix = MoveBoundsFix::Bounce;
	SetSteeringForceFlags(steeringForceFlags);
}

CSteeringBehaviorFLOCKING::~CSteeringBehaviorFLOCKING()
{
}
