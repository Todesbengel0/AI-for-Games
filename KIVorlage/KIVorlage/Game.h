#pragma once
#include "Welt.h"
#include "Steuerung.h"

class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
    // Hier ist Platz für Deine Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;

	CPlacement m_zpCameraForController;

	//Eigene Objekte
	Welt m_cSpielbrett;
	CSteuerung m_cSteuerung;
};
