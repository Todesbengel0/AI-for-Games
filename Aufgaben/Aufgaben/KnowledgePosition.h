#pragma once

#include "Knowledge.h"

class CKnowledgePosition : public CKnowledge
{
public:
	CKnowledgePosition(const CHVector* pPos);
	~CKnowledgePosition();

public:
	const CHVector* GetPos() const;

private:
	const CHVector* m_pPos;
};
