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
	m_zgMesh = m_zfWaveFront.LoadGeoTriangleTable("Geos\\elsa.obj", true);
	m_zm.MakeTextureDiffuse("textures\\elsa_texture.png");
	m_zpKinematics.AddGeo(m_zgMesh);
	m_zgMesh->SetMaterial(&m_zm);
	m_zpKinematics.Scale(4.0f);
}

void CPlayerCharacter::Update(float fTime, float fTimeDelta, CDeviceKeyboard* pzdKeyboard)
{
	CHVector vMoveDir = CHVector(0.0f, 0.0f, 0.0f);
	if (pzdKeyboard->KeyPressed(DIK_W))
	{
		vMoveDir.z -= 1.0f;
	}
	if (pzdKeyboard->KeyPressed(DIK_S))
	{
		vMoveDir.z += 1.0f;
	}
	if (pzdKeyboard->KeyPressed(DIK_A))
	{
		//Rotate Character Left (mathematisch positiv)
		m_zpKinematics.AddOrientation(UM_DEG2RAD(5.0f));
	}
	if (pzdKeyboard->KeyPressed(DIK_D))
	{
		//Rotate Character Right (mathematisch negativ)
		m_zpKinematics.AddOrientation(UM_DEG2RAD(-5.0f));
	}

	// bewegung nur, wenn positionsänderung vorhanden
	if (vMoveDir.LengthSquare() > 0.1f)
	{
		vMoveDir.z *= cosf(m_zpKinematics.GetOrientation());
		vMoveDir.x *= sinf(m_zpKinematics.GetOrientation());

		m_zpKinematics.TranslateDelta(vMoveDir);
	}
}
