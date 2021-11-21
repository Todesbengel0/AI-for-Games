#include "pch.h"
#include "Welt.h"
#include "KnowledgesInclude.h"
#include "Steuerung.h"

Welt::Welt()
{

}

Welt::~Welt()
{

}

void Welt::Init(CHVector vBoardSize /*= CHVector(80.0f, 1.0f, 40.0f)*/)
{
	m_vBoardSize = vBoardSize;

	m_SpawnRnd.SRand(int(time(nullptr)));

	// spielbrett
	m_zgBoard.Init(vBoardSize, nullptr);
	m_zmBoard.MakeTextureDiffuse("textures\\snow.png");
	m_zgBoard.SetMaterial(&m_zmBoard);
	m_zpBoard.AddGeo(&m_zgBoard);

	// player
	m_cPlayer.Init(m_vBoardSize);
	m_zpBoard.AddPlacement(&m_cPlayer.GetPlacement());

	// NPCs
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.AddKnowledge("PlayerPos", std::make_shared<CKnowledgePosition>(&m_cPlayer));

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}
	for (auto& Npc : m_cRedObjekt)
	{
		Npc.AddKnowledge("PlayerPos", std::make_shared<CKnowledgePosition>(&m_cPlayer));

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}
}

CHVector Welt::GetBoardsize()
{
	return m_vBoardSize;
}

void Welt::SpawnNpc()
{
	for (auto& npc : m_cTestobjekt)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
	for (auto& npc : m_cRedObjekt)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
}

void Welt::Update(float fTime, float fTimeDelta, CSteuerung* pSteuerung)
{
	// eigenen spieler vor anderen updaten
	m_cPlayer.Update(fTime, fTimeDelta, pSteuerung);

	// npc AI logik updates
	for (auto& npc : m_cTestobjekt)
		npc.Update(fTime, fTimeDelta, pSteuerung);
	for (auto& npc : m_cRedObjekt)
		npc.Update(fTime, fTimeDelta, pSteuerung);
}

void Welt::Fini()
{
	for (auto& npc : m_cTestobjekt)
		npc.Fini();

	for (auto& npc : m_cRedObjekt)
		npc.Fini();
}

CPlacement* Welt::getBrettPlacement()
{
	return &m_zpBoard;
}
