#include "pch.h"
#include "Welt.h"

Welt::Welt()
{

}

Welt::~Welt()
{

}

void Welt::setMaterial(CMaterial newmaterial)
{
	m_zgcBrett.SetMaterial(&newmaterial);
}

void Welt::Init(CHVector Brettsize)
{
	m_zgcBrett.Init(Brettsize, nullptr);
	m_zpBrett.AddGeo(&m_zgcBrett);
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.Init();
		m_zpBrett.AddPlacement(&Npc);
		Npc.SwitchOff();
	} 
	
	m_zhvSize = Brettsize;
}

CHVector Welt::getBoardsize()
{
	return m_zhvSize;
}

void Welt::SpawnNpc()
{
	int i = 0;
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.Spawn(m_zhvSize, ++i);
	}
}

void Welt::Fini()
{
	for (auto& Npc : m_cTestobjekt)
	{
		Npc.Fini();
	}
}

CPlacement* Welt::getBrettPlacement()
{
	return &m_zpBrett;
}
