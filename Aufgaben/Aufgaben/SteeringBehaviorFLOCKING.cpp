#include "pch.h"
#include "SteeringBehaviorFLOCKING.h"
#include "Npc.h"
#include "KnowledgeWorldCharacters.h"

CSteeringBehaviorFLOCKING::CSteeringBehaviorFLOCKING(CNpc* user, std::shared_ptr<CKnowledgeWorldCharacters> buddies, std::shared_ptr<CKnowledgeWorldCharacters> characters, float fVelocityMatchingWeight /*= 1.0f*/, float fCohesionWeight /*= 1.0f*/, float fSeperationWeight /*= 1.0f*/, float fVelocityMatchingDistance /*= 15.0f*/, float fCohesionDistance /*= 20.0f*/, float fSeperationFOVAngle /*= QUARTERPI*/, float fSeparationFOVDistance /*= 10.0f*/)
	: CSteeringBehaviorBLEND(user, NpcAIMode::Flocking)
	, m_Buddies(buddies)
	, m_Characters(characters)
	, m_fVelocityMatchingWeight(fVelocityMatchingWeight)
	, m_fCohesionWeight(fCohesionWeight)
	, m_fSeparationWeight(fSeperationWeight)
	, m_fVelocityMatchingDistance(fVelocityMatchingDistance)
	, m_fCohesionDistance(fCohesionDistance)
	, m_fSeparationFOVAngle(fSeperationFOVAngle)
	, m_fSeparationFOVDistance(fSeparationFOVDistance)
{
	m_Cohesion = std::make_shared<CSteeringBehaviorCOHESION>(user, m_Buddies, fCohesionDistance);
	m_Separation = std::make_shared<CSteeringBehaviorSEPARATION>(user, m_Characters, fSeperationFOVAngle, fSeparationFOVDistance);
	m_VelocityMatching = std::make_shared<CSteeringBehaviorVELOCITY_MATCHING>(user, m_Buddies, fVelocityMatchingDistance);
}

CSteeringBehaviorFLOCKING::~CSteeringBehaviorFLOCKING()
{
}

SSteeringForce CSteeringBehaviorFLOCKING::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;

}
