#pragma once

#include "DefaultNpc.h"
#include "RedNpc.h"

class Welt
{
public:
	Welt();
	~Welt();

	void setMaterial(CMaterial newmaterial);
	void Init(CHVector Brettsize = CHVector(80.0f, 1.0f, 40.0f));
	CHVector getBoardsize();
	void SpawnNpc();
	void Fini();

	CPlacement* getBrettPlacement();

private:
	CGeoCube m_zgcBrett;
	CPlacement m_zpBrett;
	CMaterial m_zmBrett;
	CHVector m_zhvSize;

	CDefaultNpc m_cTestobjekt[15];
	CRedNpc m_cRedObjekt[15];

};

