#pragma once

class COption;
class CAvailableOptions
{
public:
	CAvailableOptions();
	~CAvailableOptions();

public:
	void AddOption(COption* pOption);
	void RemoveOption(COption* pOption);

	void ExecutePreferred(float fTime, float fTimeDelta);

private:
	std::vector<COption*> m_Options;
};
