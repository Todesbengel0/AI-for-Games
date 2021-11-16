#include "pch.h"
#include "AvailableOptions.h"

CAvailableOptions::CAvailableOptions()
{

}

CAvailableOptions::~CAvailableOptions()
{

}

void CAvailableOptions::AddOption(COption* pOption)
{
	m_Options.emplace_back(pOption);
}

void CAvailableOptions::RemoveOption(COption* pOption)
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

void CAvailableOptions::ExecutePreferred(float fTime, float fTimeDelta)
{

}
