#include "pch.h"
#include "KnowledgeWorldCharacters.h"

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
