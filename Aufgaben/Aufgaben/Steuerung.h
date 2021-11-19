#pragma once
class CSteuerung
{
public:
	CSteuerung();
	~CSteuerung();

	void STDSteuerung(CPlacement& Objekt, float fTimeDelta);
	void Init(CCamera* Camera, CFrame* Frame);
	bool GetSchmutzporn();
	void SetSchmutzporn(bool pornoeus);
	CDeviceKeyboard* GetKeyboard();

private:
	CDeviceKeyboard m_zdKeyboard;
	CCamera* m_zc;

	float m_fCameraZoom = 0.1f;
	float m_fWS = 0.0f, m_fAD = 0.0f, m_fLR = 0.0f, m_fUD = 0.0f, m_fHR = 0.0f;
	int m_iSensitivity = 1;
	CHMat m_zhmStartPosition;
	bool m_bFirsttick = true, m_bSchmutzporn = false, m_bToggleMovement = false;
};

