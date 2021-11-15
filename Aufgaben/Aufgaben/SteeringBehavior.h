#pragma once

#include "Action.h"

class CSteeringBehavior : public CAction
{
public:
	CSteeringBehavior();
	virtual ~CSteeringBehavior();

public:
	virtual CHVector GetForce() = 0;
};
