#pragma once

#include "KnowledgeCharacter.h"

class CKnowledgePosition : public CKnowledgeCharacter
{
public:
	CKnowledgePosition(CCharacter* pCharacter);
	~CKnowledgePosition();

public:
	CHVector GetPosition() const;

private:
};
