#pragma once
#include "Octave.h"

class CPerlinNoise
{
public:
	CPerlinNoise(int numOctaves, int startValue = 1);
	~CPerlinNoise();

	/// <summary>
	/// Calculates the Perlin Noise at a specific time. PN(t) = Ei=1,m(Oi(t) * p^i)
	/// </summary>
	/// <param name="time">Time of which to get the Signal value from</param>
	/// <param name="persistance">Value how much each further Ocatave should contribute more to the final value. Default: 0.5</param>
	/// <param name="function">Interpolationfunction to use for Interpolation. Default: Function of degree five</param>
	/// <returns>Over Octaves accumulated value</returns>
	float GetValue(float time, float persistance = 0.5f, CInterpolationFunction* function = ms_DefaultInterpolationFunction);

private:
	const int m_numOctaves;
	const int m_startValue;
	COctave** m_Octaves;

	static CInterpolationFunction* ms_DefaultInterpolationFunction;
};
