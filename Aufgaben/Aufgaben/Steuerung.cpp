#include "pch.h"
#include "Steuerung.h"

CSteuerung::CSteuerung()
	: m_zc(nullptr)
{

}

CSteuerung::~CSteuerung()
{
}

void CSteuerung::STDSteuerung(CPlacement& Objekt, float fTimeDelta)
{
	if (m_bFirsttick)
	{
		m_zhmStartPosition = Objekt.GetMat();
		m_bFirsttick = false;
	}

	if (m_zdKeyboard.KeyPressed(DIK_LSHIFT))
	{
		Objekt.SetTranslationSensitivity(150.f);
	}
	else
	{
		Objekt.SetTranslationSensitivity(50.f);
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
		Objekt.SetMat(m_zhmStartPosition);
	}
	if (m_zdKeyboard.KeyPressed(DIK_L))
	{
		m_fHR = -1;
	}
	if (m_zdKeyboard.KeyPressed(DIK_O))
	{
		m_fHR = 1;
	}

	if (m_zdKeyboard.KeyDown(DIK_SPACE))
	{
		m_bSchmutzporn = true;
	}


	Objekt.Move(fTimeDelta, false, m_fAD, m_fWS, m_fHR, m_fLR, m_fUD);

	
}

void CSteuerung::Init(CCamera* Camera, CFrame* Frame)
{
	m_zc = Camera;
	Frame->AddDeviceKeyboard(&m_zdKeyboard);
}

bool CSteuerung::GetSchmutzporn()
{
	return m_bSchmutzporn;
}

void CSteuerung::SetSchmutzporn(bool pornoeus)
{
	m_bSchmutzporn = pornoeus;
}

CDeviceKeyboard* CSteuerung::GetKeyboard()
{
	return &m_zdKeyboard;
}
