#pragma once
class CNpc
{
public:
	CNpc();
	~CNpc();

	void Init();

private:
	CGeo m_zgSchneemann;
	CPlacement m_zpSchneemann;
	CFileWavefront m_zfwSchneemann;

};

