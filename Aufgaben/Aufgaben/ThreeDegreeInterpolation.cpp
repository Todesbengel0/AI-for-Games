#include "pch.h"
#include "ThreeDegreeInterpolation.h"

float CThreeDegreeInterpolation::Interpolation(float functionvalue)
{
    return 3 * std::pow(functionvalue, 2)
        - 2 * std::pow(functionvalue, 3);
}
