#pragma once

#include "Action.h"
#include "SteeringForce.h"

class CSteeringBehavior : public CAction
{
public:
	CSteeringBehavior(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
	virtual ~CSteeringBehavior();

public:
	// final, da erbende Steering Behaviors GetForce() implementieren sollen, nicht Update()
	void Update(float fTime, float fTimeDelta) final;
	virtual SSteeringForce GetForce(float fTimeDelta) = 0;

protected:
	//static void Limit(CHVector& v, float maxLength);
	static void Limit(CHVector& v, float minLength, float maxLength);
	static void Limit(float& angle, float maxAngle);
};
