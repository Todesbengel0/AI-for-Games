#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Update(float fTime, float fTimeDelta)
{
	m_AvailableOptions.ExecutePreferred(fTime, fTimeDelta);
}

void CNpc::AddKnowledge(std::string name, std::shared_ptr<CKnowledge> knowledge)
{
	m_Knowledges[name] = knowledge;
}

void CNpc::RemoveKnowledge(std::string name)
{
	auto it = m_Knowledges.find(name);
	if (it == m_Knowledges.end())
		return;
	m_Knowledges.erase(it);
}
