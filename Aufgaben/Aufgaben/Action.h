#pragma once

#include "Option.h"

class CAction : public COption
{
public:
	CAction(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
	~CAction();
};
