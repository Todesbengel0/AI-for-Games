#pragma once

#include "Knowledge.h"

class CCharacter;
class CKnowledgeCharacter : public CKnowledge
{
public:
	CKnowledgeCharacter(CCharacter* pCharacter);
	~CKnowledgeCharacter();

protected:
	CCharacter* m_pCharacter;
};
