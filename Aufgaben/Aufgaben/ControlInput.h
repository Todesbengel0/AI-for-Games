#pragma once

#include "NpcAIMode.h"

class CControlInput
{
public:
	CControlInput();
	~CControlInput();

	void STDSteuerung(CPlacement& rzpCamera, float fTimeDelta);
	void Init(CCamera* Camera, CFrame* Frame);
	bool GetShouldSpawn();
	void SetShouldSpawn(bool bShouldSpawn);
	CDeviceKeyboard* GetKeyboard();
	NpcAIMode GetNpcAIMode() const;

private:
	void CamSteuerung(CPlacement& rzpCamera, float fTimeDelta);

private:
	CDeviceKeyboard m_zdKeyboard;
	CCamera* m_zc;

	float m_fCameraZoom = 0.1f;
	float m_fWS = 0.0f, m_fAD = 0.0f, m_fLR = 0.0f, m_fUD = 0.0f, m_fHR = 0.0f;
	int m_iSensitivity = 1;
	CHMat m_zhmStartPosition;
	bool m_bFirsttick = true, m_bShouldSpawn = false, m_bToggleMovement = false;

	NpcAIMode m_NpcAIMode;
};

