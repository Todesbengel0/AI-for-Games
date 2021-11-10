#pragma once
#include "Octave.h"

class CPerlinNoise
{
public:
	CPerlinNoise(int numOctaves, int startValue = 1);
	~CPerlinNoise();

	// PN(t) = Ei=1,m(Oi(t) * p^i)
	float GetValue(float time, float persistance = 0.5f);

private:
	const int m_numOctaves;
	const int m_startValue;
	COctave** m_Octaves;
};
