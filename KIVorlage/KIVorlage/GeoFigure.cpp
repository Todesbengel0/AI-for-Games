#include "pch.h"
#include "GeoFigure.h"

GeoFigure::GeoFigure() = default;

GeoFigure::~GeoFigure() = default;

void GeoFigure::Init(float fSize /*= 1.0f*/)
{

	// Material
	m_zm.Init();

	//CGeoSphere::Init();
}

void GeoFigure::Fini()
{

}
