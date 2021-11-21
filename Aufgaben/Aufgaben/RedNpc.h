#pragma once

#include "Npc.h"

class CRedNpc : public CNpc
{
public:
    CRedNpc();
    ~CRedNpc();

protected:
	void InitMaterial() override;
};

