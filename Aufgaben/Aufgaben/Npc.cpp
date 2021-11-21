#include "pch.h"
#include "Npc.h"
#include "SteeringBehaviorsInclude.h"
#include "KnowledgesInclude.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Init(CHVector dimension)
{
	// alle NPCs sind schneemänner
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	InitMaterial();

	InitOptions();

	CCharacter::Init(dimension);
}

void CNpc::InitOptions()
{
	std::shared_ptr<CKnowledgePosition> knowledgePlayerPos = GetKnowledge<CKnowledgePosition>("PlayerPos");
	if (knowledgePlayerPos)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorKinematicSEEK>(this, knowledgePlayerPos));
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorKinematicFLEE>(this, knowledgePlayerPos));
	}
}

void CNpc::RandomSpawn(CHVector dimension, CRandom& rRnd)
{
	float xSpawn = rRnd.RandFt() * dimension.x;
	float zSpawn = rRnd.RandFt() * dimension.z;
	float yRot = rRnd.RandFt() * PI;

	Spawn(CHVector(xSpawn, 0.0f, zSpawn), CHVector(0.0f, yRot, 0.0f));
}

void CNpc::Update(float fTime, float fTimeDelta, CSteuerung* pSteuerung)
{
	m_AvailableOptions.UpdatePreferred(fTime, fTimeDelta, pSteuerung);
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
