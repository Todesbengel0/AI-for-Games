#pragma once

#include "AIComponent.h"
#include "NpcAIMode.h"

class CNpc;

class COption : public CAIComponent
{
public:
	COption(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
	~COption();

public:
	NpcAIMode GetNpcAIMode() const;
	virtual void Update(float fTime, float fTimeDelta) = 0;

protected:
	CNpc* m_pUser;

private:
	NpcAIMode m_NpcAIMode;
};
