#include "pch.h"
#include "KnowledgeWorldBorder.h"
#include "World.h"

CKnowledgeWorldBorder::CKnowledgeWorldBorder(CWorld* pWorld)
	: CKnowledgeWorld(pWorld)
{
}

CKnowledgeWorldBorder::~CKnowledgeWorldBorder()
{
}

CHVector CKnowledgeWorldBorder::GetBoardSize() const
{
	return m_pWorld->GetBoardSize();
}
