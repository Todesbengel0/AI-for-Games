#pragma once

#include "SteeringBehavior.h"

class CKnowledgePosition;
class CKnowledgeWorldBorder;
class CSteeringBehaviorDynamicESCAPE : public CSteeringBehavior
{
public:
	CSteeringBehaviorDynamicESCAPE(CNpc* user, std::shared_ptr<CKnowledgePosition> target, std::shared_ptr<CKnowledgeWorldBorder> worldBorder);
	~CSteeringBehaviorDynamicESCAPE();

public:
	SSteeringForce GetForce() override;

private:
	std::shared_ptr<CKnowledgePosition> m_pKnowledgePosition;
	std::shared_ptr<CKnowledgeWorldBorder> m_pWorldBorder;
};

