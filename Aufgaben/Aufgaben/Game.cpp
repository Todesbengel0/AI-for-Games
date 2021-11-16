#include "pch.h"
#include "Game.h"
#include "Welt.h"
#include "Steuerung.h"
#include "DefaultNpc.h"
#include "NormalDistribution.h"
#include "PerlinNoise.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Random-Seedilazation
	srand(int(time(nullptr)));

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

	// Random Tests / Exports nach Excel
	PlotNormalDistributionFloat();
	PlotNormalDistributionInt();
	PlotPerlinNoise();
}

void CGame::PlotNormalDistributionFloat()
{
	std::ofstream ofs("normal_float_export.csv", std::ios::out | std::ios::trunc);
	CNormalDistribution nd;

	// force comma delimiter instead of point
	ofs.imbue(std::locale("German_germany"));

	for (int i = 0; i < 200; ++i)
	{
		ofs << nd.RandNormFt(-10.0f, 10.0f) << ";";
	}
}

void CGame::PlotNormalDistributionInt()
{
	std::ofstream ofs("normal_int_export.csv", std::ios::out | std::ios::trunc);
	CNormalDistribution nd;

	for (int i = 0; i < 200; ++i)
	{
		ofs << nd.RandNormInt(-10, 10) << ";";
	}
}

void CGame::PlotPerlinNoise()
{
	std::ofstream ofs("perlin_noise_export.csv", std::ios::out | std::ios::trunc);
	CPerlinNoise pn(5, 1);

	// force comma delimiter instead of point
	ofs.imbue(std::locale("German_germany"));

	for (int i = 0; i < 100; ++i)
	{
		ofs << pn.GetValue((float)i * 0.01f) << ";";
	}
	ofs << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		ofs << pn.GetValue((float)i * 0.01f, 0.5f, &CThreeDegreeInterpolation()) << ";";
	}
	ofs << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		ofs << pn.GetValue((float)i * 0.01f, 0.5f, &CLinearInterpolation()) << ";";
	}
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	m_zr.Tick(fTimeDelta);

	// GPU Grill vermeiden :)
	::Sleep(1);

	//Steuerung muss jeden Tick aufgerufen werden
	m_cSteuerung.STDSteuerung(m_zpCamera, fTimeDelta);

	if (m_cSteuerung.GetSchmutzporn())
	{
		m_cSpielbrett.SpawnNpc();
		m_cSteuerung.SetSchmutzporn(false);
	}
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
	m_cSpielbrett.Fini();
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}
