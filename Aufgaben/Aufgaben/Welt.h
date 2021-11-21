#pragma once

#include "PlayerCharacter.h"
#include "DefaultNpc.h"
#include "RedNpc.h"

class CSteuerung;
class Welt
{
public:
	Welt();
	~Welt();

public:
	void Init(CHVector vBoardSize = CHVector(80.0f, 1.0f, 40.0f));
	void Fini();

	void SpawnNpc();
	void Update(float fTime, float fTimeDelta, CSteuerung* pSteuerung);

public:
	CHVector GetBoardsize();
	CPlacement* getBrettPlacement();

private:
	CGeoCube m_zgBoard;
	CPlacement m_zpBoard;
	CMaterial m_zmBoard;
	CHVector m_vBoardSize;

	CPlayerCharacter m_cPlayer;
	CDefaultNpc m_cTestobjekt[15];
	CRedNpc m_cRedObjekt[15];

	CRandom m_SpawnRnd;
};

