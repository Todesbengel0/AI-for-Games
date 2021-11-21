#include "pch.h"
#include "PlayerCharacter.h"
#include "Steuerung.h"

CPlayerCharacter::CPlayerCharacter()
{
}

CPlayerCharacter::~CPlayerCharacter()
{
}

void CPlayerCharacter::Init(CHVector dimension)
{
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\elsa.obj", true);
	m_zm.MakeTextureDiffuse("textures\\elsa_texture.png");
	m_zgMesh->SetMaterial(&m_zm);

	// skalierungsfix
	m_zpModel.Scale(4.0f);

	// bewegungseigenschaften
	m_zpKinematics.SetMaxMovementForce(15.0f);
	m_zpKinematics.SetMaxRotationVelocity(UM_DEG2RAD(90.0f));

	CCharacter::Init(dimension);
}

void CPlayerCharacter::Update(float fTime, float fTimeDelta, CSteuerung* pSteuerung)
{
	float fSW = 0.0f;
	float fLR = 0.0f;

	if (pSteuerung->GetKeyboard()->KeyPressed(DIK_W))
	{
		fSW = -1.0f;
	}
	if (pSteuerung->GetKeyboard()->KeyPressed(DIK_S))
	{
		fSW = 1.0f;
	}
	if (pSteuerung->GetKeyboard()->KeyPressed(DIK_A))
	{
		fLR = -1.0f;
	}
	if (pSteuerung->GetKeyboard()->KeyPressed(DIK_D))
	{
		fLR = 1.0f;
	}

	float fAD = 0.0f; // keine DIREKTE links- rechtsverschiebung!
	float fFR = 0.0f; // keine hoch- runterverschiebung!
	float fUD = 0.0f; // keine hoch- runterdrehung!
	m_zpKinematics.GetTopPlacement().Move(fTimeDelta, true, fAD, fSW, fFR, fLR, fUD);
}
