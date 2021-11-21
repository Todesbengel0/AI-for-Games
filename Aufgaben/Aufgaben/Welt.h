#pragma once

#include "PlayerCharacter.h"
#include "DefaultNpc.h"
#include "RedNpc.h"

class Welt
{
public:
	Welt();
	~Welt();

public:
	void Init(CHVector vBoardSize = CHVector(80.0f, 1.0f, 40.0f));
	void Fini();

	void SpawnNpc();

public:
	CHVector GetBoardsize();
	CPlacement* getBrettPlacement();

private:
	CGeoCube m_zgcBrett;
	CPlacement m_zpBrett;
	CMaterial m_zmBrett;
	CHVector m_zhvSize;

	CPlayerCharacter m_cPlayer;
	CDefaultNpc m_cTestobjekt[15];
	CRedNpc m_cRedObjekt[15];
};

