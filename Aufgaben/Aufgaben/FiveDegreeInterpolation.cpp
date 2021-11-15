#include "pch.h"
#include "FiveDegreeInterpolation.h"

float CFiveDegreeInterpolation::Interpolation(float functionvalue)
{
	// S(t) = 10*t^3 - 15*t^4 + 6*t^5
	return 10 * std::powf(functionvalue, 3.0f)
		- 15 * std::powf(functionvalue, 4.0f)
		+ 6 * std::powf(functionvalue, 5.0f);
}
