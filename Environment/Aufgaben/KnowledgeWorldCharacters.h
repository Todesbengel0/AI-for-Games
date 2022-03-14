#pragma once

#include "KnowledgeWorld.h"

class CCharacter;

class CKnowledgeWorldCharacters : public CKnowledgeWorld
{
public:
	using character_vec_t = std::vector<CCharacter*>;

	CKnowledgeWorldCharacters(CWorld* pWorld, const character_vec_t& Characters);
	~CKnowledgeWorldCharacters();

	const character_vec_t& GetCharacters() const;
	const character_vec_t GetCharactersNear(CHVector position, float maxDistance = 10.0f);
	const character_vec_t GetCharactersNear(CCharacter* source, float maxDistance = 10.0f);
	const character_vec_t GetCharactersInFOV(CHVector position, CHVector viewDir, float maxDiffAngle = QUARTERPI, float maxDistance = 25.0f);
	const character_vec_t GetCharactersInFOV(CCharacter* source, float maxDiffAngle = QUARTERPI, float maxDistance = 25.0f);

private:
	character_vec_t m_Characters;
};
