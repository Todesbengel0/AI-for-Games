#pragma once
#include "Npc.h"
class CDefaultNpc : public CNpc
{
public:
	CDefaultNpc();
	~CDefaultNpc();

protected:
	void InitMaterial() override;
};

