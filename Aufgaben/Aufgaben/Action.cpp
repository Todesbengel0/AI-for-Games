#include "pch.h"
#include "Action.h"

CAction::CAction(CNpc* user, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: COption(user, npcAiMode)
{
}

CAction::~CAction()
{
}
