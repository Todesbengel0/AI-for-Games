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
	// alle NPCs sind Schneemänner
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	InitMaterial();

	InitOptions();

	// Bewegungseigenschaften
	m_zpKinematics.SetMinMovementForce(1.0f);
	m_zpKinematics.SetMaxMovementForce(8.0f);

	m_zpKinematics.SetMaxMovementIncrease(4.0f);
	m_zpKinematics.SetMaxMovementDecrease(10.0f);	// wenn zu niedrig, schießen über Ziel hinaus und oszillieren
	m_zpKinematics.SetMaxRotationForce(UM_DEG2RAD(90.0f));

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
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorCOHESION>(this, knowledgeBuddies));
	}

	std::shared_ptr<CKnowledgeWorldCharacters> knowledgeCharacters = GetKnowledge<CKnowledgeWorldCharacters>("Characters");
	if (knowledgeCharacters)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorSEPARATION>(this, knowledgeCharacters));
	}

	if (knowledgeBuddies && knowledgeCharacters)
	{
		m_AvailableOptions.AddOption(std::make_shared<CSteeringBehaviorFLOCKING>(this, knowledgeBuddies, knowledgeCharacters));
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
	//auto pos = m_zpKinematics.GetPosition();
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
