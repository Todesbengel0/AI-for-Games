#pragma once

#include "Knowledge.h"

class CWorld;
class CKnowledgeWorld : public CKnowledge
{
public:
	CKnowledgeWorld(CWorld* pWelt);
	~CKnowledgeWorld();

protected:
	CWorld* m_pWorld;
};
