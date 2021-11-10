#pragma once

class COctave
{
public:
	COctave(int rank);
	~COctave();

	float GetSignal(float time);

private:
	static float S(float functionvalue);
	const int m_Rank;
	const int m_NumSignals;
	float* m_TimeMarks; //tj
	float* m_Signals;
	
};
