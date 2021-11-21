#pragma once

#include "Kinematics.h"

class CSteuerung;
class CCharacter
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual void Init(CHVector dimension);
	void Spawn(CHVector vPos = CHVector(0.0f, 0.0f, 0.0f), CHVector vRot = CHVector(0.0f, 0.0f, 0.0f));
	virtual void Update(float fTime, float fTimeDelta, CSteuerung* pSteuerung) = 0;
	void Fini();

// getter / setter
public:
	CKinematics& GetKinematics();

protected:
	// Placement bezogene Daten
	CKinematics m_zpKinematics;
	CPlacement m_zpModelFix;

	// Geometrie bezogene Daten
	CGeoTriangleTable* m_zgMesh;
	CFileWavefront m_zfWaveFront;
	CMaterial m_zm;
};
