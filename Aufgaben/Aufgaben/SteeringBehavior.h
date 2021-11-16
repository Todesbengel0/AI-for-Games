#pragma once

#include "Action.h"

class CSteeringBehavior : public CAction
{
public:
	CSteeringBehavior();
	virtual ~CSteeringBehavior();

public:
	void Update(float fTime, float fTimeDelta);
	virtual CHVector GetForce() = 0;
};
