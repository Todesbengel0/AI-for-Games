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

public:
	// Placement bezogene Daten
	CKinematics m_zp;

	// Geometrie bezogene Daten
	CGeoTriangleTable* m_zgSchneemann;
	CFileWavefront m_zfwSchneemann;
	CMaterial m_zmSchneemannBlack;
	CMaterial m_zmSchneemannRed;
};
