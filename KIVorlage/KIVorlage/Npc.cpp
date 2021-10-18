#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Init()
{
	m_zgSchneemann = m_zfwSchneemann.LoadGeoTriangleTable("Geos\\Schneemann_mit_Hut.obj", true);
	m_zmSchneemann.MakeTextureDiffuse("textures\\schneemann_farbe.png");
	m_zgSchneemann->SetMaterial(&m_zmSchneemann);
	this->AddGeo(m_zgSchneemann);
}

void CNpc::Fini()
{
	delete m_zgSchneemann;
}
