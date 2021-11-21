#pragma once

#include "Character.h"
#include "AvailableOptions.h"

class CKnowledge;

class CNpc : public CCharacter
{
public:
	CNpc();
	~CNpc();

public:
	void RandomSpawn(CHVector dimension, CRandom& rRnd);
	void Update(float fTime, float fTimeDelta, CDeviceKeyboard* pzdKeyboard) override;
	void AddKnowledge(std::string name, std::shared_ptr<CKnowledge> knowledge);
	void RemoveKnowledge(std::string name);

protected:
	CAvailableOptions m_AvailableOptions;
	std::map<std::string, std::shared_ptr<CKnowledge>> m_Knowledges;
};

