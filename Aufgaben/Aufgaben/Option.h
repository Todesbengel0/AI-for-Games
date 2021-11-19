#pragma once

#include "AIComponent.h"

class CNpc;

class COption : public CAIComponent
{
public:
	COption(CNpc* user);
	~COption();

public:
	virtual void Execute() = 0;

protected:
	CNpc* m_pUser;
};
