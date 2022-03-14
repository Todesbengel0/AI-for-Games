#include "pch.h"
#include "Option.h"
#include "NPC.h"

COption::COption(CNpc* user, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: m_pUser(user)
	, m_NpcAIMode(npcAiMode)
{
}

COption::~COption()
{
}

NpcAIMode COption::GetNpcAIMode() const
{
	return m_NpcAIMode;
}
