#pragma once
class CNpc : public CPlacement
{
public:
	CNpc();
	~CNpc();

	void Init();
	void Fini();
	

private:
	CGeoTriangleTable* m_zgSchneemann;
	CFileWavefront m_zfwSchneemann;
	CMaterial m_zmSchneemann;

};

