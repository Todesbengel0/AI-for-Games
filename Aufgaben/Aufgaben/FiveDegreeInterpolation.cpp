#include "pch.h"
#include "FiveDegreeInterpolation.h"

float CFiveDegreeInterpolation::Interpolation(float functionvalue)
{
	// S(t) = 10*t^3 - 15*t^4 + 6*t^5
	return 10 * std::pow(functionvalue, 3)
		- 15 * std::pow(functionvalue, 4)
		+ 6 * std::pow(functionvalue, 5);
}
