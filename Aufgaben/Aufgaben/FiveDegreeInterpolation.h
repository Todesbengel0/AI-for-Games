#pragma once
#include "InterpolationFunction.h"

class CFiveDegreeInterpolation :
    public CInterpolationFunction
{
public:
    float Interpolation(float functionvalue) override;
};

