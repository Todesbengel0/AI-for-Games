#include "pch.h"
#include "Steuerung.h"

CSteuerung::CSteuerung()
	: m_zc(nullptr)
	, m_NpcAIMode(NpcAIMode::Idle)
{
}

CSteuerung::~CSteuerung()
{
}

void CSteuerung::STDSteuerung(CPlacement& rzpCamera, float fTimeDelta)
{
	// Kamerasteuerung
	CamSteuerung(rzpCamera, fTimeDelta);
	
	// andere Keys
	if (m_zdKeyboard.KeyDown(DIK_SPACE))
	{
		m_bShouldSpawn = true;
	}

	if (m_zdKeyboard.KeyDown(DIK_1))
	{
		m_NpcAIMode = NpcAIMode::Idle;
	}
	if (m_zdKeyboard.KeyDown(DIK_2))
	{
		m_NpcAIMode = NpcAIMode::KinematicSeek;
	}
	if (m_zdKeyboard.KeyDown(DIK_3))
	{
		m_NpcAIMode = NpcAIMode::KinematicFlee;
	}
}

void CSteuerung::CamSteuerung(CPlacement& rzpCamera, float fTimeDelta)
{
	if (m_bFirsttick)
	{
		m_zhmStartPosition = rzpCamera.GetMat();
		m_bFirsttick = false;
	}

	if (m_zdKeyboard.KeyPressed(DIK_LSHIFT))
	{
		rzpCamera.SetTranslationSensitivity(150.f);
	}
	else
	{
		rzpCamera.SetTranslationSensitivity(50.f);
	}

	m_fWS = 0; m_fAD = 0; m_fLR = 0; m_fUD = 0; m_fHR = 0;

	if (m_zdKeyboard.KeyPressed(DIK_G))
	{
		m_fCameraZoom += fTimeDelta;
		m_zc->SetFov(m_fCameraZoom);
	}
	if (m_zdKeyboard.KeyPressed(DIK_Y))
	{
		m_fCameraZoom -= fTimeDelta;
		m_zc->SetFov(m_fCameraZoom);
	}
	m_bToggleMovement = m_zdKeyboard.KeyPressed(DIK_LCONTROL);
	if (m_zdKeyboard.KeyPressed(DIK_UPARROW))
	{
		m_bToggleMovement ? (m_fUD = 1.0f) : (m_fWS = -1.0f);
	}
	if (m_zdKeyboard.KeyPressed(DIK_DOWNARROW))
	{
		m_bToggleMovement ? (m_fUD = -1.0f) : (m_fWS = 1.0f);
	}
	if (m_zdKeyboard.KeyPressed(DIK_LEFTARROW))
	{
		(m_bToggleMovement ? m_fLR : m_fAD) = -1.0f;
	}
	if (m_zdKeyboard.KeyPressed(DIK_RIGHTARROW))
	{
		(m_bToggleMovement ? m_fLR : m_fAD) = 1.0f;
	}
	if (m_zdKeyboard.KeyPressed(DIK_R))
	{
		rzpCamera.SetMat(m_zhmStartPosition);
	}
	if (m_zdKeyboard.KeyPressed(DIK_L))
	{
		m_fHR = -1;
	}
	if (m_zdKeyboard.KeyPressed(DIK_O))
	{
		m_fHR = 1;
	}

	rzpCamera.Move(fTimeDelta, false, m_fAD, m_fWS, m_fHR, m_fLR, m_fUD);
}

void CSteuerung::Init(CCamera* Camera, CFrame* Frame)
{
	m_zc = Camera;
	Frame->AddDeviceKeyboard(&m_zdKeyboard);
}

bool CSteuerung::GetShouldSpawn()
{
	return m_bShouldSpawn;
}

void CSteuerung::SetShouldSpawn(bool bShouldSpawn)
{
	m_bShouldSpawn = bShouldSpawn;
}

CDeviceKeyboard* CSteuerung::GetKeyboard()
{
	return &m_zdKeyboard;
}

NpcAIMode CSteuerung::GetNpcAIMode() const
{
	return m_NpcAIMode;
}
