#pragma once
#include "World.h"
#include "ControlInput.h"

class CGame
{
public:
	CGame();																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame();																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat

private:
	static void PlotNormalDistributionFloat();
	static void PlotNormalDistributionInt();
	static void PlotPerlinNoise();

private:
    // Hier ist Platz f�r Deine Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;

	CPlacement m_zpCameraForController;

	//Eigene Objekte
	CWorld m_cSpielbrett;
	CControlInput m_cSteuerung;
};
