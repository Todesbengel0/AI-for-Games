#pragma once

#include "SteeringBehavior.h"

struct SWeightedSteeringBehavior
{
	std::shared_ptr<CSteeringBehavior> Behavior;
	float Weight;
};

class CSteeringBehaviorBLEND : public CSteeringBehavior
{
	using behavior_vec_t = std::vector<SWeightedSteeringBehavior>;

public:
	CSteeringBehaviorBLEND(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
	CSteeringBehaviorBLEND(CNpc* user, behavior_vec_t behaviors, NpcAIMode npcAiMode = NpcAIMode::Idle);
	~CSteeringBehaviorBLEND();

protected:
	void AddBehavior(SWeightedSteeringBehavior behavior);
	void RemoveBehavior(std::shared_ptr<CSteeringBehavior> behavior);
	void SetSteeringForceFlags(SSteeringForceFlags flags);

public:
	SSteeringForce GetForce(float fTimeDelta) final;

private:
	SSteeringForceFlags m_SteeringForceFlags;
	behavior_vec_t m_Behaviors;
};
