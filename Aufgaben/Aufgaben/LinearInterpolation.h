#pragma once
#include "InterpolationFunction.h"
class CLinearInterpolation :
    public CInterpolationFunction
{
public:
    float Interpolation(float functionvalue) override;
};

