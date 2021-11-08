#include "pch.h"
#include "Octave.h"

COctave::COctave(int rank)
	: m_Rank(rank), m_NumSignals(std::pow(2,rank-1)+1)
{
	m_TimeMarks = new float[m_NumSignals];
	m_Signals = new float[m_NumSignals];
	m_TimeMarks[0] = 0;
	for (int i = 1; i < m_NumSignals; ++i)
	{
		m_TimeMarks[i] = i / (m_NumSignals - 1);
	}
	CRandom rnd;
	rnd.SRand(rank * time(NULL));
	for (int i = 0; i < m_NumSignals; ++i)
	{
		m_Signals[i] = rnd.RandFr();
	}
}

COctave::~COctave()
{
	delete[] m_Signals;
	delete[] m_TimeMarks;
}

float COctave::GetSignal(float time)
{
	int index = 0;
	for (int i = 1; i < m_NumSignals; ++i)
	{
		if (time <= m_TimeMarks[i])
		{
			index = i;
			break;
		}
	}
	return m_Signals[index - 1] + (m_Signals[index] - m_Signals[index - 1]) * S((time - m_TimeMarks[index - 1]) / (m_TimeMarks[index] - m_TimeMarks[index - 1]));
}

float COctave::S(float time)
{
	return 10 * std::pow(time,3) - 15 * std::pow(time,4) + 6 * std::pow(time,5);
}
