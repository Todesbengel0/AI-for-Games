#include "pch.h"
#include "KnowledgeWorldCharacters.h"
#include "Character.h"

CKnowledgeWorldCharacters::CKnowledgeWorldCharacters(CWorld* pWorld, const character_vec_t& Characters)
	: CKnowledgeWorld(pWorld)
	, m_Characters(Characters)
{
}

CKnowledgeWorldCharacters::~CKnowledgeWorldCharacters()
{
}

const CKnowledgeWorldCharacters::character_vec_t& CKnowledgeWorldCharacters::GetCharacters() const
{
	return m_Characters;
}

const CKnowledgeWorldCharacters::character_vec_t CKnowledgeWorldCharacters::GetCharactersNear(CHVector position, float maxDistance /*= 10.0f*/)
{
	character_vec_t nearbyCharacters;
	for (auto character : m_Characters)
	{
		// NPC zum Ziel
		CHVector vToTarget = character->GetKinematics().GetPosition() - position;
		float fDist = vToTarget.Length();
		if (fDist <= maxDistance)
		{
			nearbyCharacters.emplace_back(character);
		}
	}
	return nearbyCharacters;
}

const CKnowledgeWorldCharacters::character_vec_t CKnowledgeWorldCharacters::GetCharactersNear(CCharacter* source, float maxDistance /*= 10.0f*/)
{
	character_vec_t nearbyCharacters;
	for (auto character : m_Characters)
	{
		if (character == source)
			continue;

		// NPC zum Ziel
		CHVector vToTarget = character->GetKinematics().GetPosition() - source->GetKinematics().GetPosition();
		float fDist = vToTarget.Length();
		if (fDist <= maxDistance)
		{
			nearbyCharacters.emplace_back(character);
		}
	}
	return nearbyCharacters;
}

const CKnowledgeWorldCharacters::character_vec_t CKnowledgeWorldCharacters::GetCharactersInFOV(CHVector position, CHVector viewDir, float maxDiffAngle /*= QUARTERPI*/, float maxDistance /*= 25.0f*/)
{
	character_vec_t fovCharacters;
	for (auto character : m_Characters)
	{
		// NPC zum Ziel
		CHVector vToTarget = character->GetKinematics().GetPosition() - position;
		float fDist = vToTarget.Length();
		// Winkel zwischen Blickrichtung und Target
		float fAngleToTarget = AngleDiff(AngleVektoriaToZX(viewDir), AngleVektoriaToZX(vToTarget));
		if (fAngleToTarget <= maxDiffAngle && fDist <= maxDistance)
			fovCharacters.emplace_back(character);
	}
	return fovCharacters;
}

const CKnowledgeWorldCharacters::character_vec_t CKnowledgeWorldCharacters::GetCharactersInFOV(CCharacter* source, float maxDiffAngle /*= QUARTERPI*/, float maxDistance /*= 25.0f*/)
{
	character_vec_t fovCharacters;
	for (auto character : m_Characters)
	{
		if (character == source)
			continue;

		// NPC zum Ziel
		CHVector vToTarget = character->GetKinematics().GetPosition() - source->GetKinematics().GetPosition();
		float fDist = vToTarget.Length();
		// Winkel zwischen Blickrichtung und Target
		float fAngleToTarget = AngleDiff(source->GetKinematics().GetOrientationAngleZX(), AngleVektoriaToZX(vToTarget));
		if (fAngleToTarget <= maxDiffAngle && fDist <= maxDistance)
			fovCharacters.emplace_back(character);
	}
	return fovCharacters;
}