#pragma once

#include "KnowledgeWorld.h"

class CKnowledgeWorldBorder : public CKnowledgeWorld
{
public:
	CKnowledgeWorldBorder(CWorld* pWorld);
	~CKnowledgeWorldBorder();

public:
	CHVector GetBoardSize() const;
};
