#pragma once
#include "Octave.h"

class CPerlinNoise
{
public:
	CPerlinNoise(int numOctaves, int startValue);
	~CPerlinNoise();

	float GetValue(float time, float persistance);


private:
	const int m_numOctaves;
	const int m_startValue;
	int m_persistance;
	COctave** m_Octaves;
};
