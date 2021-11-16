#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
{

}

CCharacter::~CCharacter()
{

}

void CCharacter::Init()
{
	m_zgSchneemann = m_zfwSchneemann.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	m_zmSchneemannBlack.MakeTextureDiffuse("textures\\schneeman_farbe.png");
	m_zmSchneemannRed.MakeTextureDiffuse("textures\\schneeman_rot.png");
	m_zp.AddGeo(m_zgSchneemann);
}

void CCharacter::Fini()
{
	delete m_zgSchneemann;
}

void CCharacter::Spawn(CHVector dimension, int noise)
{
	CRandom random;
	random.SRand(int(time(nullptr)) * noise);
	float xSpawn = random.RandFt() * dimension.x;
	float zSpawn = random.RandFt() * dimension.z;
	float yRot = random.RandFt() * PI;
	SwitchOn();
	RotateY(yRot);
	TranslateDelta(xSpawn, dimension.y, zSpawn);
}

Vektoria::CPlacement& CCharacter::GetKinematics()
{
	return m_zp;
}

