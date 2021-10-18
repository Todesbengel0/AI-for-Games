#pragma once
class CNpc : public CPlacement
{
public:
	CNpc();
	~CNpc();

	void Init();
	void Fini();
	void Spawn(CHVector dimension, int noise);

protected:
	CGeoTriangleTable* m_zgSchneemann;
	CFileWavefront m_zfwSchneemann;
	CMaterial m_zmSchneemannBlack;
	CMaterial m_zmSchneemannRed;

};

