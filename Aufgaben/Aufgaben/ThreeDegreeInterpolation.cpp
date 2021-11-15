#include "pch.h"
#include "ThreeDegreeInterpolation.h"

float CThreeDegreeInterpolation::Interpolation(float functionvalue)
{
    return 3 * std::powf(functionvalue, 2.0f)
        - 2 * std::powf(functionvalue, 3.0f);
}
