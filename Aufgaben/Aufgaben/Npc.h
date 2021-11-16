#pragma once

#include "Character.h"
#include "AvailableOptions.h"

class CNpc : public CCharacter
{
public:
	CNpc();
	~CNpc();

public:
	void Update(float fTime, float fTimeDelta);

protected:
	CAvailableOptions m_AvailableOptions;
};

