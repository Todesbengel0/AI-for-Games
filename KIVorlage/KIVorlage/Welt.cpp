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
	m_cTestobjekt.Init();
	m_zpBrett.AddPlacement(&m_cTestobjekt);
	m_cTestobjekt.SwitchOff();
}

CHVector Welt::getBoardsize()
{
	return m_zhvSize;
}

void Welt::SpawnNpc()
{
	m_cTestobjekt.SwitchOn();
	m_cTestobjekt.Translate(m_zhvSize);

}

void Welt::Fini()
{
	m_cTestobjekt.Fini();
}

CPlacement* Welt::getBrettPlacement()
{
	return &m_zpBrett;
}
