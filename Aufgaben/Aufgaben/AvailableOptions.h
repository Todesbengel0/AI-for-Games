#pragma once

class COption;
class CSteuerung;
class CAvailableOptions
{
public:
	CAvailableOptions();
	~CAvailableOptions();

public:
	void AddOption(std::shared_ptr<COption> pOption);
	void RemoveOption(std::shared_ptr<COption> pOption);

	void UpdatePreferred(float fTime, float fTimeDelta, CSteuerung* pSteuerung);

private:
	std::vector<std::shared_ptr<COption>> m_Options;
};
