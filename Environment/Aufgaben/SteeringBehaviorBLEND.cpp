#include "pch.h"
#include "SteeringBehaviorBLEND.h"

CSteeringBehaviorBLEND::CSteeringBehaviorBLEND(CNpc* user, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: CSteeringBehavior(user, npcAiMode)
{
}

CSteeringBehaviorBLEND::CSteeringBehaviorBLEND(CNpc* user, behavior_vec_t behaviors, NpcAIMode npcAiMode /*= NpcAIMode::Idle*/)
	: CSteeringBehavior(user, npcAiMode)
	, m_Behaviors(std::move(behaviors))
{
}

CSteeringBehaviorBLEND::~CSteeringBehaviorBLEND()
{
}

void CSteeringBehaviorBLEND::AddBehavior(SWeightedSteeringBehavior behavior)
{
	m_Behaviors.emplace_back(std::move(behavior));
}

void CSteeringBehaviorBLEND::RemoveBehavior(std::shared_ptr<CSteeringBehavior> behavior)
{
	for (auto it = m_Behaviors.begin(); it != m_Behaviors.end(); ++it)
	{
		if (it->Behavior == behavior)
		{
			m_Behaviors.erase(it);
			return;
		}
	}
}

void CSteeringBehaviorBLEND::SetSteeringForceFlags(SSteeringForceFlags flags)
{
	m_SteeringForceFlags = flags;
}

SSteeringForce CSteeringBehaviorBLEND::GetForce(float fTimeDelta)
{
	SSteeringForce resForce;
	resForce.Flags = m_SteeringForceFlags;

	for (const auto& behavior : m_Behaviors)
	{
		resForce += behavior.Behavior->GetForce(fTimeDelta) * behavior.Weight;
	}

	return resForce;
}
