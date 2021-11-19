#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
	: m_zgMesh(nullptr)
{

}

CCharacter::~CCharacter()
{

}

void CCharacter::Init()
{
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	m_zpKinematics.AddGeo(m_zgMesh);
}

void CCharacter::Fini()
{
	delete m_zgMesh;
}

void CCharacter::Spawn(CHVector dimension, int noise)
{
	CRandom random;
	random.SRand(int(time(nullptr)) * noise);
	float xSpawn = random.RandFt() * dimension.x;
	float zSpawn = random.RandFt() * dimension.z;
	float yRot = random.RandFt() * PI;
	m_zpKinematics.SwitchOn();
	m_zpKinematics.RotateY(yRot);
	m_zpKinematics.TranslateDelta(xSpawn, dimension.y, zSpawn);
}

CKinematics& CCharacter::GetKinematics()
{
	return m_zpKinematics;
}

