#include "pch.h"
#include "RedNpc.h"
#include "SteeringBehaviorsInclude.h"
#include "KnowledgesInclude.h"

CRedNpc::CRedNpc()
{
}

CRedNpc::~CRedNpc()
{
}

void CRedNpc::InitMaterial()
{
	m_zm.MakeTextureDiffuse("textures\\schneeman_rot.png");
	m_zgMesh->SetMaterial(&m_zm);
}

void CRedNpc::InitOptions()
{
	CNpc::InitOptions();
	std::shared_ptr<CKnowledgePosition> knowledgePlayerPos = GetKnowledge<CKnowledgePosition>("PlayerPos");
	if (knowledgePlayerPos)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorRealisticSEEK>(this, knowledgePlayerPos));
	}
	std::shared_ptr<CKnowledgeWorldBorder> knowledgeWorldBorder = GetKnowledge<CKnowledgeWorldBorder>("WorldBorder");
	if (knowledgePlayerPos && knowledgeWorldBorder)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorDynamicESCAPE>(this, knowledgePlayerPos, knowledgeWorldBorder));
	}
}
