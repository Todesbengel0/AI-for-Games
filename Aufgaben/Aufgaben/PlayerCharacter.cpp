#include "pch.h"
#include "PlayerCharacter.h"

CPlayerCharacter::CPlayerCharacter()
{
}

CPlayerCharacter::~CPlayerCharacter()
{
}

void CPlayerCharacter::Init()
{
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\Schneeman_mit_Hut.obj", true);
	m_zm.MakeTextureDiffuse("textures\\schneeman_farbe.png");
	m_zpKinematics.AddGeo(m_zgMesh);
	m_zgMesh->SetMaterial(&m_zm);
}

void CPlayerCharacter::Update(float fTime, float fTimeDelta, CDeviceKeyboard* zdKeyboard)
{
	CHVector vMoveDir = CHVector(0.0f, 0.0f, 0.0f);
	if (zdKeyboard->KeyPressed(DIK_W))
	{
		vMoveDir.z += 1.0f;
	}
	if (zdKeyboard->KeyPressed(DIK_S))
	{
		vMoveDir.z -= 1.0f;
	}
	if (zdKeyboard->KeyPressed(DIK_A))
	{
		//Rotate Character Left (mathematisch positiv)
		m_zpKinematics.AddOrientation(UM_DEG2RAD(5.0f));
		
	}
	if (zdKeyboard->KeyPressed(DIK_D))
	{
		//Rotate Character Right (mathematisch negativ)
		m_zpKinematics.AddOrientation(UM_DEG2RAD(-5.0f));
	}
	vMoveDir.z *= cosf(m_zpKinematics.GetOrientation());
	vMoveDir.x *= sinf(m_zpKinematics.GetOrientation());

}
