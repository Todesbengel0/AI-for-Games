#include "pch.h"
#include "PerlinNoise.h"

CPerlinNoise::CPerlinNoise(int numOctaves, int startValue)
	: m_numOctaves(numOctaves), m_startValue(startValue), m_persistance(0.5f)
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

float CPerlinNoise::GetValue(float time, float persistance)
{
	float output = 0;
	for (int i = 0; i < m_numOctaves; ++i)
	{
		output += m_Octaves[i]->GetSignal(time) * std::pow(persistance, m_startValue + i);
	}
	return output;
}
