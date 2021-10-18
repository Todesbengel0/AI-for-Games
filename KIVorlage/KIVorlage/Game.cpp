#include "pch.h"
#include "Game.h"
#include "Welt.h"
#include "Steuerung.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.AddPlacement(&m_zpCameraForController);



	//Spielbrett
	m_cSpielbrett.Init();
	m_zs.AddPlacement(m_cSpielbrett.getBrettPlacement());

	//Steuerung
	m_cSteuerung.Init(&m_zc, &m_zf);

	//Standardeinstellungen für die Camera als Ausgang
	m_zpCamera.TranslateZ(210.0f);
	m_zpCamera.RotateXDelta(UM_DEG2RAD(330));
	m_zc.SetNearClipping(0.001f);
	m_zc.SetFarClipping(1000.0f);

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	m_zr.Tick(fTimeDelta);

	// GPU Grill vermeiden :)
	::Sleep(1);

	//Steuerung muss jeden Tick aufgerufen werden
	m_cSteuerung.STDSteuerung(m_zpCamera, fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

