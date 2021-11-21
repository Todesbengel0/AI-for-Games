#pragma once

#include "Character.h"

class CPlayerCharacter : public CCharacter
{
public:
	CPlayerCharacter();
	~CPlayerCharacter();

public:
	void Init() override;
	void Update(float fTime, float fTimeDelta, CDeviceKeyboard* pzdKeyboard) override;
};
