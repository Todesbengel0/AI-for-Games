#pragma once
#include "InterpolationFunction.h"

class CThreeDegreeInterpolation :
    public CInterpolationFunction
{
public:
    float Interpolation(float functionvalue) override;
};

