#include "pch.h"
#include "Octave.h"

COctave::COctave(int rank)
	: m_Rank(rank)
	, m_NumSignals(int(std::pow(2, rank - 1) + 1))
{
	m_TimeSignalTuples = new SOctaveTuple[m_NumSignals];

	// Erstelle tj
	m_TimeSignalTuples[0].TimeMark = 0; // t1 = 0
	for (int i = 1; i < m_NumSignals; ++i)
	{
		m_TimeSignalTuples[i].TimeMark = (float)i / (float)(m_NumSignals - 1);	// tj = j / n
	}

	// Erstelle sj
	CRandom rnd;
	rnd.SRand(rank * int(time(nullptr)));
	for (int i = 0; i < m_NumSignals; ++i)
	{
		m_TimeSignalTuples[i].Signal = rnd.RandFr();	// sj = Random
	}
}

COctave::~COctave()
{
	delete[] m_TimeSignalTuples;
}

// Oi(t)
float COctave::GetSignal(float time, CInterpolationFunction* function)
{
	// Zeit-Intervall in der Oktave
	int tuple_index = 0;
	for (int i = 1; i < m_NumSignals; ++i)
	{
		if (time <= m_TimeSignalTuples[i].TimeMark)
		{
			tuple_index = i;
			break;
		}
	}

	// (t - tj)/(tj+1 - tj)
	float time_fraction = (time - m_TimeSignalTuples[tuple_index - 1].TimeMark)
		/ (m_TimeSignalTuples[tuple_index].TimeMark - m_TimeSignalTuples[tuple_index - 1].TimeMark);

	// Oi(t) = sj + (sj+1 - sj) * S((t - tj)/(tj+1 - tj))
	return m_TimeSignalTuples[tuple_index - 1].Signal
		+ (m_TimeSignalTuples[tuple_index].Signal - m_TimeSignalTuples[tuple_index - 1].Signal) * function->Interpolation(time_fraction);
}
