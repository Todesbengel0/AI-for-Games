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
	m_zpTop.AddPlacement(&m_zpKinematics.GetTopPlacement());

	// dimension / bounds
	m_zpKinematics.SetBounds(-dimension, dimension);

	// zwischenplacement, um NUR model auszurichten, kann leer sein
	m_zpModel.AddGeo(m_zgMesh);
	m_zpModel.TranslateYDelta(dimension.y);
	m_zpKinematics.GetLowestPlacement().AddPlacement(&m_zpModel);
}

void CCharacter::Spawn(CHVector vPos /*= CHVector(0.0f, 0.0f, 0.0f)*/, float fOrientationAngle /*= 0.0f*/)
{
	m_zpKinematics.ResetPosRot();
	m_zpKinematics.ChangeOrientation(fOrientationAngle);
	assert(std::abs(fOrientationAngle - m_zpKinematics.GetOrientationAngleXZ()) < 0.001f);	// check correct orientation computing
	m_zpKinematics.SetPosition(vPos);

	m_zpTop.SwitchOn();
}

void CCharacter::Fini()
{
	delete m_zgMesh;
}

CPlacement& CCharacter::GetPlacement()
{
	return m_zpTop;
}

CKinematics& CCharacter::GetKinematics()
{
	return m_zpKinematics;
}

