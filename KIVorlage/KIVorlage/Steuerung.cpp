#include "pch.h"
#include "Steuerung.h"

CSteuerung::CSteuerung()
{

}

CSteuerung::~CSteuerung()
{
}

void CSteuerung::STDSteuerung(CPlacement& Objekt, float fTimeDelta)
{
	if (m_bFirsttick)
	{
		m_zhmAnfangspos = Objekt.GetMat();
		m_bFirsttick = false;
	}

	if (m_zdTastatur.KeyPressed(DIK_LSHIFT))
	{
		Objekt.SetTranslationSensitivity(150.f);
	}
	else
	{
		Objekt.SetTranslationSensitivity(50.f);
	}

	m_iWS = 0; m_iAD = 0; m_iLR = 0; m_iUD = 0; m_iHR = 0;

	if (m_zdTastatur.KeyPressed(DIK_G))
	{
		Kamerazoom += fTimeDelta;
		m_zc->SetFov(Kamerazoom);
	}
	if (m_zdTastatur.KeyPressed(DIK_Y))
	{
		Kamerazoom -= fTimeDelta;
		m_zc->SetFov(Kamerazoom);
	}

	if (m_zdTastatur.KeyPressed(DIK_W))
	{
		m_iWS = -1;
	}
	if (m_zdTastatur.KeyPressed(DIK_S))
	{
		m_iWS = 1;
	}
	if (m_zdTastatur.KeyPressed(DIK_A))
	{
		m_iAD = -1;
	}
	if (m_zdTastatur.KeyPressed(DIK_D))
	{
		m_iAD = 1;
	}
	if (m_zdTastatur.KeyPressed(DIK_LEFTARROW))
	{
		m_iLR = -1;
	}
	if (m_zdTastatur.KeyPressed(DIK_RIGHTARROW))
	{
		m_iLR = 1;
	}
	if (m_zdTastatur.KeyPressed(DIK_UPARROW))
	{
		m_iUD = 1;
	}
	if (m_zdTastatur.KeyPressed(DIK_DOWNARROW))
	{
		m_iUD = -1;
	}
	if (m_zdTastatur.KeyPressed(DIK_R))
	{
		Objekt.SetMat(m_zhmAnfangspos);
	}
	if (m_zdTastatur.KeyPressed(DIK_L))
	{
		m_iHR = -1;
	}
	if (m_zdTastatur.KeyPressed(DIK_O))
	{
		m_iHR = 1;
	}

	if (m_zdTastatur.KeyPressed(DIK_SPACE))
	{
		m_bSchmutzporn = true;
	}


	Objekt.Move(fTimeDelta, false, m_iAD, m_iWS, m_iHR, m_iLR, m_iUD);

	
}

void CSteuerung::Init(CCamera* Camera, CFrame* Frame)
{
	m_zc = Camera;
	Frame->AddDeviceKeyboard(&m_zdTastatur);
}

bool CSteuerung::GetSchmutzporn()
{
	return m_bSchmutzporn;
}

void CSteuerung::SetSchmutzporn(bool pornoeus)
{
	m_bSchmutzporn = pornoeus;
}

CDeviceKeyboard* CSteuerung::getKeyboard()
{
	return &m_zdTastatur;
}
