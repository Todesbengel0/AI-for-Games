#include "pch.h"
#include "Welt.h"

Welt::Welt()
{

}

Welt::~Welt()
{

}

void Welt::Init(CHVector vBoardSize /*= CHVector(80.0f, 1.0f, 40.0f)*/)
{
	m_zhvSize = vBoardSize;

	// spielbrett
	m_zgcBrett.Init(vBoardSize, nullptr);
	m_zmBrett.MakeTextureDiffuse("textures\\snow.png");
	m_zgcBrett.SetMaterial(&m_zmBrett);
	m_zpBrett.AddGeo(&m_zgcBrett);

	// player
	m_cPlayer.Init();
	m_zpBrett.AddPlacement(&m_cPlayer.GetKinematics());

	// NPCs
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.Init();
		m_zpBrett.AddPlacement(&Npc.GetKinematics());
		Npc.GetKinematics().SwitchOff();
	}
	for (auto& Npc : m_cRedObjekt)
	{
		Npc.Init();
		m_zpBrett.AddPlacement(&Npc.GetKinematics());
		Npc.GetKinematics().SwitchOff();
	}
}

CHVector Welt::GetBoardsize()
{
	return m_zhvSize;
}

void Welt::SpawnNpc()
{
	int i = 0;
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.RandomSpawn(m_zhvSize, ++i);
	}
	for (auto& Npc : m_cRedObjekt)
	{
		Npc.RandomSpawn(m_zhvSize, ++i);
	}
}

void Welt::Fini()
{
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.Fini();
	}

	for (auto& Npc : m_cRedObjekt)
	{
		Npc.Fini();
	}
}

CPlacement* Welt::getBrettPlacement()
{
	return &m_zpBrett;
}
