#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
	: m_zgMesh(nullptr)
{

}

CCharacter::~CCharacter()
{

}

void CCharacter::Init(CHVector dimension)
{
	// dimension / bounds
	CAABB bounds(-dimension, dimension);
	m_zpKinematics.SetMoveRange(bounds);

	// zwischenplacement, um NUR model auszurichten, kann leer sein
	m_zpModelFix.AddGeo(m_zgMesh);
	m_zpModelFix.TranslateYDelta(dimension.y);
	m_zpKinematics.AddPlacement(&m_zpModelFix);
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

