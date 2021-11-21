#pragma once

#include "Kinematics.h"

class CCharacter
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual void Init();
	void Spawn(CHVector vPos = CHVector(0.0f, 0.0f, 0.0f), CHVector vRot = CHVector(0.0f, 0.0f, 0.0f));
	void Fini();

// getter / setter
public:
	CKinematics& GetKinematics();

protected:
	// Placement bezogene Daten
	CKinematics m_zpKinematics;

	// Geometrie bezogene Daten
	CGeoTriangleTable* m_zgMesh;
	CFileWavefront m_zfWaveFront;
	CMaterial m_zm;
};
