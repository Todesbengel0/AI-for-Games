#pragma once
#include "interpolation.h"

struct SOctaveTuple
{
	float TimeMark;	// tj
	float Signal;	// sj
};

class COctave
{
public:
	COctave(int rank);
	~COctave();

	// Oi(t)
	float GetSignal(float time, CInterpolationFunction* function);

private:
	const int m_Rank;
	const int m_NumSignals;
	SOctaveTuple* m_TimeSignalTuples; // Tupel(tj,sj)
};
