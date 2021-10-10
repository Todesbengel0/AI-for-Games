#pragma once

class GeoFigure : public CGeoSphere
{
public:
	GeoFigure();
	~GeoFigure();

public:
	void Init(float fSize = 1.0f);
	void Fini();

private:
	CMaterial m_zm;

};
