#pragma once

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
	float GetSignal(float time);

private:
	// Eine mögliche S-Funktion
	// Kann ausgewechselt werden!
	static float S(float functionvalue);

	const int m_Rank;
	const int m_NumSignals;
	SOctaveTuple* m_TimeSignalTuples; // Tupel(tj,sj)
};
