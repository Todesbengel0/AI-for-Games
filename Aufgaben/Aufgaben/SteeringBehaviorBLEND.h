#pragma once

#include "SteeringBehavior.h"


class CSteeringBehaviorBLEND : public CSteeringBehavior
{
public:
	CSteeringBehaviorBLEND(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
};
