#pragma once

#include "Kinematics.h"

class CCharacter
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual void Init();
	void Fini();
	void Spawn(CHVector dimension, int noise);

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
