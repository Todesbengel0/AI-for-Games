#pragma once

#include "Kinematics.h"

class CControlInput;
class CCharacter
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual void Init(CHVector dimension);
	void Spawn(CHVector vPos = CHVector(0.0f, 0.0f, 0.0f), float fOrientationAngle = 0.0f);
	virtual void Update(float fTime, float fTimeDelta, CControlInput* pSteuerung) = 0;
	void Fini();

// getter / setter
public:
	CPlacement& GetPlacement();
	CKinematics& GetKinematics();

protected:
	// Placement bezogene Daten
	CPlacement m_zpTop;	// nur um alle Placements zu aktivieren / deaktivieren
	CKinematics m_zpKinematics; // kinematisch gesteuerte Position & Rotation
	CPlacement m_zpModel; // Model

	// Geometrie bezogene Daten
	CGeoTriangleTable* m_zgMesh;
	CFileWavefront m_zfWaveFront;
	CMaterial m_zm;
};
