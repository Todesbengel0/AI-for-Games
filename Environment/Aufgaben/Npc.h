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
	void Init(CHVector dimension) override;
	void RandomSpawn(CHVector dimension, CRandom& rRnd);
	void Update(float fTime, float fTimeDelta, CControlInput* pSteuerung) override;
	void AddKnowledge(std::string name, std::shared_ptr<CKnowledge> knowledge);
	void RemoveKnowledge(std::string name);

protected:
	virtual void InitMaterial() = 0;

	virtual void InitOptions();
	template<typename KnowledgeTy>
	std::shared_ptr<KnowledgeTy> GetKnowledge(std::string name);

protected:
	CAvailableOptions m_AvailableOptions;
	std::map<std::string, std::shared_ptr<CKnowledge>> m_Knowledges;
};



///<summary>
///<para>Sucht Knowledge unter gegebenem Namen und validiert, ob diese vom richtigen Typ ist.</para>
///<para>Wenn nicht gefunden oder invalide, returned null</para>
///</summary>
///<param name="name">Name der Knowledge</param>
template<typename KnowledgeTy>
std::shared_ptr<KnowledgeTy> CNpc::GetKnowledge(std::string name)
{
	auto it = m_Knowledges.find(name);
	if (it == m_Knowledges.end())
		return nullptr;

	return std::dynamic_pointer_cast<KnowledgeTy>(it->second);
}