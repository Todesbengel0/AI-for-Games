#include "pch.h"
#include "PerlinNoise.h"

/// Create a PerlinNoise with numOctaves and startValue = 1
CPerlinNoise::CPerlinNoise(int numOctaves)
	: m_numOctaves(numOctaves), m_startValue(1)
{
	m_Octaves = new COctave * [m_numOctaves];
	for (int i = 0; i < m_numOctaves; ++i)
	{
		m_Octaves[i] = new COctave(i + 1);
	}
}

CPerlinNoise::CPerlinNoise(int numOctaves, int startValue)
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

/// <summary>
/// Calculates the Perlin Noise at a specific time.
/// </summary>
/// <param name="time">Time of which to get the Signal value from</param>
/// <param name="persistance">Value how much each further Ocatave should contribute more to the final value.</param>
/// <returns></returns>
float CPerlinNoise::GetValue(float time, float persistance)
{
	float output = 0;
	for (int i = 0; i < m_numOctaves; ++i)
	{
		output += m_Octaves[i]->GetSignal(time) * std::pow(persistance, m_startValue + i);
	}
	return output;
}

/// <summary>
/// Calculates the Perlin Noise at a specific time with persistance = 0.5
/// </summary>
/// <param name="time">Time of which to get the Signal value from</param>
/// <returns>Signal value at time</returns>
float CPerlinNoise::GetValue(float time)
{
	return GetValue(time, 0.5);
}
