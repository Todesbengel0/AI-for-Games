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
	CDeviceKeyboard* getKeyboard();

private:
	CDeviceKeyboard m_zdTastatur;
	CCamera* m_zc;

	float Kamerazoom = 0.1;
	float m_iWS = 0, m_iAD = 0, m_iLR = 0, m_iUD = 0, m_iHR = 0;
	int m_isensitivity = 1;
	CHMat m_zhmAnfangspos;
	bool m_bFirsttick = true, m_bSchmutzporn = false;
};

