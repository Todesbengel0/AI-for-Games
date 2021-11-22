#include "pch.h"
#include "World.h"
#include "KnowledgesInclude.h"
#include "ControlInput.h"

CWorld::CWorld()
{

}

CWorld::~CWorld()
{

}

void CWorld::Init(CHVector vBoardSize /*= CHVector(80.0f, 1.0f, 40.0f)*/)
{
	m_vBoardSize = vBoardSize;

	m_SpawnRnd.SRand(int(time(nullptr)));

	// spielbrett
	m_zgBoard.Init(vBoardSize, nullptr);
	m_zmBoard.MakeTextureDiffuse("textures\\snow.png");
	m_zgBoard.SetMaterial(&m_zmBoard);
	m_zpBoard.AddGeo(&m_zgBoard);

	// knowledges
	auto knowledgeWorldBorder = std::make_shared<CKnowledgeWorldBorder>(this);
	auto knowledgePlayerPos = std::make_shared<CKnowledgePosition>(&m_cPlayer);

	// player
	m_cPlayer.Init(m_vBoardSize);
	m_zpBoard.AddPlacement(&m_cPlayer.GetPlacement());

	// NPCs
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.AddKnowledge("WorldBorder", knowledgeWorldBorder);
		Npc.AddKnowledge("PlayerPos", knowledgePlayerPos);

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}
	for (auto& Npc : m_cRedObjekt)
	{
		Npc.AddKnowledge("WorldBorder", knowledgeWorldBorder);
		Npc.AddKnowledge("PlayerPos", knowledgePlayerPos);

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}
}

CHVector CWorld::GetBoardSize()
{
	return m_vBoardSize;
}

void CWorld::SpawnNpc()
{
	for (auto& npc : m_cTestobjekt)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
	for (auto& npc : m_cRedObjekt)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
}

void CWorld::Update(float fTime, float fTimeDelta, CControlInput* pSteuerung)
{
	// eigenen spieler vor anderen updaten
	m_cPlayer.Update(fTime, fTimeDelta, pSteuerung);

	// npc AI logik updates
	for (auto& npc : m_cTestobjekt)
		npc.Update(fTime, fTimeDelta, pSteuerung);
	for (auto& npc : m_cRedObjekt)
		npc.Update(fTime, fTimeDelta, pSteuerung);
}

void CWorld::Fini()
{
	for (auto& npc : m_cTestobjekt)
		npc.Fini();

	for (auto& npc : m_cRedObjekt)
		npc.Fini();

	m_cPlayer.Fini();
}

CPlacement* CWorld::getBrettPlacement()
{
	return &m_zpBoard;
}
