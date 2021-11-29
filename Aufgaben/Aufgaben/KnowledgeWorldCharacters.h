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

private:
	character_vec_t m_Characters;
};
