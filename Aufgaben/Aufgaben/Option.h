#pragma once

#include "AIComponent.h"

class CNPC;

class COption : public CAIComponent
{
public:
	COption(CNPC* user);
	~COption();

public:
	virtual void Execute() = 0;

protected:
	CNPC* m_user;
};
