#include "pch.h"
#include "KnowledgePosition.h"

CKnowledgePosition::CKnowledgePosition(const CHVector* pPos)
	: m_pPos(pPos)
{
}

CKnowledgePosition::~CKnowledgePosition()
{
}

const CHVector* CKnowledgePosition::GetPos() const
{
	return m_pPos;
}
