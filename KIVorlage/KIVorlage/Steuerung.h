#pragma once
class CSteuerung
{
public:
	CSteuerung();
	~CSteuerung();

	void STDSteuerung(CPlacement& Objekt, float fTimeDelta);
	void Init(CCamera* Camera, CFrame* Frame);
	CDeviceKeyboard* getKeyboard();

private:
	CDeviceKeyboard m_zdTastatur;
	CCamera* m_zc;

	float Kamerazoom = 0.1;
	float m_fXCurser = 0, m_fYCurser = 0, m_fXCurserold = 0, m_fYCurserold = 0;
	float m_iWS = 0, m_iAD = 0, m_iLR = 0, m_iUD = 0, m_iHR = 0;
	float m_frRelativeX = 0, m_frRelativeY = 0, m_flRelativeZ;
	int m_isensitivity = 1;
	CHMat m_zhmAnfangspos;
	bool m_bFirsttick = true;
};

