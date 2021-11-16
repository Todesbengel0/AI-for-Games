#pragma once

#include "KnowledgeCharacter.h"

class CKnowledgePosition : public CKnowledgeCharacter
{
public:
	CKnowledgePosition(CCharacter* pCharacter);
	~CKnowledgePosition();

public:
	CHVector GetPos() const;

private:
};
