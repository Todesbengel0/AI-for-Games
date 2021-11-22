#include "pch.h"
#include "DefaultNpc.h"
#include "SteeringBehaviorsInclude.h"
#include "KnowledgesInclude.h"

CDefaultNpc::CDefaultNpc()
{
}

CDefaultNpc::~CDefaultNpc()
{
}

void CDefaultNpc::InitMaterial()
{
	m_zm.MakeTextureDiffuse("textures\\schneeman_farbe.png");
	m_zgMesh->SetMaterial(&m_zm);
}

void CDefaultNpc::InitOptions()
{
	CNpc::InitOptions();
	std::shared_ptr<CKnowledgePosition> knowledgePlayerPos = GetKnowledge<CKnowledgePosition>("PlayerPos");
	if (knowledgePlayerPos)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorDynamicFLEE>(this, knowledgePlayerPos));
	}
}
