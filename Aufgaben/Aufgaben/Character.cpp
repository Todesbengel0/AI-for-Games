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

void CCharacter::Spawn(CHVector vPos /*= CHVector(0.0f, 0.0f, 0.0f)*/, CHVector vRot /*= CHVector(0.0f, 0.0f, 0.0f)*/)
{
	m_zpKinematics.RotateX(vRot.x);
	m_zpKinematics.RotateYDelta(vRot.y);
	m_zpKinematics.RotateZDelta(vRot.z);
	m_zpKinematics.TranslateDelta(vPos);
	m_zpKinematics.SwitchOn();
}

void CCharacter::Fini()
{
	delete m_zgMesh;
}

CKinematics& CCharacter::GetKinematics()
{
	return m_zpKinematics;
}

