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

	// bewegungseigenschaften
	m_zpKinematics.SetMaxMovementForce(8.0f);
	m_zpKinematics.SetMaxRotationForce(UM_DEG2RAD(90.0f));
	m_zpKinematics.SetMaxMovementAcceleration(2.5f);

	CCharacter::Init(dimension);
}

void CNpc::InitOptions()
{
	std::shared_ptr<CKnowledgePosition> knowledgePlayerPos = GetKnowledge<CKnowledgePosition>("PlayerPos");
	if (knowledgePlayerPos)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorKinematicSEEK>(this, knowledgePlayerPos));
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorKinematicFLEE>(this, knowledgePlayerPos));
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorDynamicARRIVE>(this, knowledgePlayerPos));
	}

	std::shared_ptr<CKnowledgeWorldBorder> knowledgeWorldBorder = GetKnowledge<CKnowledgeWorldBorder>("WorldBorder");
	if (knowledgeWorldBorder)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorDynamicWANDER>(this, knowledgeWorldBorder));
	}

	std::shared_ptr<CKnowledgeWorldCharacters> knowledgeBuddies = GetKnowledge<CKnowledgeWorldCharacters>("Buddies");
	if (knowledgeBuddies)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorVELOCITY_MATCHING>(this, knowledgeBuddies));
	}
}

void CNpc::RandomSpawn(CHVector dimension, CRandom& rRnd)
{
	float xSpawn = rRnd.RandFt() * dimension.x;
	float zSpawn = rRnd.RandFt() * dimension.z;
	float yRot = rRnd.RandFt() * PI;

	Spawn(CHVector(xSpawn, 0.0f, zSpawn), yRot);
}

void CNpc::Update(float fTime, float fTimeDelta, CControlInput* pSteuerung)
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
