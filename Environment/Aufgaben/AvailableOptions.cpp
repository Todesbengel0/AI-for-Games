#include "pch.h"
#include "AvailableOptions.h"
#include "SteeringBehaviorsInclude.h"
#include "ControlInput.h"

CAvailableOptions::CAvailableOptions()
{
}

CAvailableOptions::~CAvailableOptions()
{
}

void CAvailableOptions::AddOption(std::shared_ptr<COption> pOption)
{
	m_Options.emplace_back(pOption);
}

void CAvailableOptions::RemoveOption(std::shared_ptr<COption> pOption)
{
	for (auto it = m_Options.begin(); it != m_Options.end(); ++it)
	{
		if (*it == pOption)
		{
			m_Options.erase(it);
			return;
		}
	}
}

void CAvailableOptions::UpdatePreferred(float fTime, float fTimeDelta, CControlInput* pSteuerung)
{
	for (const auto& it : m_Options)
	{
		if (it->GetNpcAIMode() == pSteuerung->GetNpcAIMode())
			it->Update(fTime, fTimeDelta);
	}
}
