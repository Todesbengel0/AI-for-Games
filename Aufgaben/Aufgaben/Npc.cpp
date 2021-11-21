#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::RandomSpawn(CHVector dimension, int noise)
{
	CRandom random;
	random.SRand(int(time(nullptr)) * noise);

	float xSpawn = random.RandFt() * dimension.x;
	float zSpawn = random.RandFt() * dimension.z;
	float yRot = random.RandFt() * PI;

	Spawn(CHVector(xSpawn, dimension.y, zSpawn), CHVector(0.0f, yRot, 0.0f));
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
