#pragma once
#include "Octave.h"

class CPerlinNoise
{
public:
	CPerlinNoise(int numOctaves);
	CPerlinNoise(int numOctaves, int startValue);
	~CPerlinNoise();

	float GetValue(float time, float persistance);
	float GetValue(float time);


private:
	const int m_numOctaves;
	const int m_startValue;
	COctave** m_Octaves;
};
