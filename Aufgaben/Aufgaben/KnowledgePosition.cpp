#include "pch.h"
#include "KnowledgePosition.h"
#include "Character.h"

CKnowledgePosition::CKnowledgePosition(CCharacter* pCharacter)
	: CKnowledgeCharacter(pCharacter)
{
}

CKnowledgePosition::~CKnowledgePosition()
{
}

CHVector CKnowledgePosition::GetPosition() const
{
	return m_pCharacter->GetKinematics().GetPosition();
}
