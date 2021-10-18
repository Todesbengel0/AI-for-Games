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
}

CPlacement* Welt::getBrettPlacement()
{
	return &m_zpBrett;
}
