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
	auto knowledgeWorldCharactersDefault = std::make_shared<CKnowledgeWorldCharacters>(this, ArrayToPointerVector<CCharacter*>(m_DefaultNpcs));
	auto knowledgeWorldCharactersRed = std::make_shared<CKnowledgeWorldCharacters>(this, ArrayToPointerVector<CCharacter*>(m_RedNpcs));
	std::vector<CCharacter*> allCharacters = ArrayConcat<CCharacter*>(m_DefaultNpcs, m_RedNpcs);
	allCharacters.emplace_back(&m_cPlayer);
	auto knowledgeWorldCharactersAll = std::make_shared<CKnowledgeWorldCharacters>(this, allCharacters);
	auto knowledgePlayerPos = std::make_shared<CKnowledgePosition>(&m_cPlayer);

	// player
	m_cPlayer.Init(m_vBoardSize);
	m_zpBoard.AddPlacement(&m_cPlayer.GetPlacement());

	// NPCs
	for (auto& Npc : m_DefaultNpcs)
	{
		Npc.AddKnowledge("WorldBorder", knowledgeWorldBorder);
		Npc.AddKnowledge("PlayerPos", knowledgePlayerPos);
		Npc.AddKnowledge("Buddies", knowledgeWorldCharactersDefault);
		Npc.AddKnowledge("Characters", knowledgeWorldCharactersAll);

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}
	for (auto& Npc : m_RedNpcs)
	{
		Npc.AddKnowledge("WorldBorder", knowledgeWorldBorder);
		Npc.AddKnowledge("PlayerPos", knowledgePlayerPos);
		Npc.AddKnowledge("Buddies", knowledgeWorldCharactersRed);
		Npc.AddKnowledge("Characters", knowledgeWorldCharactersAll);

		Npc.Init(m_vBoardSize);
		m_zpBoard.AddPlacement(&Npc.GetPlacement());
		Npc.GetPlacement().SwitchOff();
	}

#ifdef _DEBUG
	m_zmDebugNpc.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zgDebugNpc.Init(CHVector(0.5f, 2.0f, 0.5f), &m_zmDebugNpc);
	m_zpDebugNpc.AddGeo(&m_zgDebugNpc);
	m_zpDebugNpc.TranslateY(7.5f);
	m_DefaultNpcs[0].GetKinematics().GetTopPlacement().AddPlacement(&m_zpDebugNpc);
#endif // _DEBUG
}

CHVector CWorld::GetBoardSize()
{
	return m_vBoardSize;
}

void CWorld::SpawnNpc()
{
	for (auto& npc : m_DefaultNpcs)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
	for (auto& npc : m_RedNpcs)
		npc.RandomSpawn(m_vBoardSize, m_SpawnRnd);
}

void CWorld::Update(float fTime, float fTimeDelta, CControlInput* pSteuerung)
{
	// eigenen spieler vor anderen updaten
	m_cPlayer.Update(fTime, fTimeDelta, pSteuerung);

	// npc AI logik updates
	for (auto& npc : m_DefaultNpcs)
		npc.Update(fTime, fTimeDelta, pSteuerung);
	for (auto& npc : m_RedNpcs)
		npc.Update(fTime, fTimeDelta, pSteuerung);
}

void CWorld::Fini()
{
	for (auto& npc : m_DefaultNpcs)
		npc.Fini();

	for (auto& npc : m_RedNpcs)
		npc.Fini();

	m_cPlayer.Fini();
}

CPlacement* CWorld::getBrettPlacement()
{
	return &m_zpBoard;
}
