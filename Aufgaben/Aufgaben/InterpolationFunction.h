#pragma once
class CInterpolationFunction
{
public:
	virtual ~CInterpolationFunction() {};
	virtual float Interpolation(float functionvalue) = 0;

};