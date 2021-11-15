#include "pch.h"
#include "PerlinNoise.h"

CPerlinNoise::CPerlinNoise(int numOctaves, int startValue /*= 1*/)
	: m_numOctaves(numOctaves), m_startValue(startValue)
{
	m_Octaves = new COctave*[m_numOctaves];
	for (int i = 0; i < m_numOctaves; ++i)
	{
		m_Octaves[i] = new COctave(startValue + i);
	}
}

CPerlinNoise::~CPerlinNoise()
{
	for (int i = 0; i < m_numOctaves; ++i)
		delete m_Octaves[i];
	delete[] m_Octaves;
}


CFiveDegreeInterpolation g_FDI;
CInterpolationFunction* CPerlinNoise::ms_DefaultInterpolationFunction = &g_FDI;

float CPerlinNoise::GetValue(float time, float persistance /*= 0.5f*/, CInterpolationFunction* function /*= ms_DefaultInterpolationFunction*/, bool bNormalize /* = false*/)
{
	// PN(t) = Ei=1,m(Oi(t) * p^i)
	float output = 0.0f;
	float ratio = 0.0f;
	for (int i = 0; i < m_numOctaves; ++i)
	{
		output += m_Octaves[i]->GetSignal(time, function) * std::powf(persistance, float(m_startValue + i));
		ratio += std::powf(persistance, float(m_startValue + i));
	}
	if (bNormalize)
		output /= ratio;
	return output;
}
