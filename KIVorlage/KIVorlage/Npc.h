#pragma once
class CNpc : public CPlacement
{
public:
	CNpc();
	~CNpc();

	void Init();
	void Fini();
	void Spawn(CHVector dimension, int noise);

private:
	CGeoTriangleTable* m_zgSchneemann;
	CFileWavefront m_zfwSchneemann;
	CMaterial m_zmSchneemann;

};

