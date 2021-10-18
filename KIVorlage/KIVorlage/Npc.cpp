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
	m_zgSchneemann = m_zfwSchneemann.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	m_zmSchneemannBlack.MakeTextureDiffuse("textures\\schneeman_farbe.png");
	m_zmSchneemannRed.MakeTextureDiffuse("textures\\schneeman_rot.png");
	this->AddGeo(m_zgSchneemann);
}

void CNpc::Fini()
{
	delete m_zgSchneemann;
}

void CNpc::Spawn(CHVector dimension, int noise)
{
	CRandom random;
	random.SRand(time(NULL) * noise);
	float xSpawn = random.RandFt() * dimension.x;
	float zSpawn = random.RandFt() * dimension.z;
	float yRot = random.RandFt() * PI;
	SwitchOn();
	RotateY(yRot);
	TranslateDelta(xSpawn, dimension.y, zSpawn);
}
