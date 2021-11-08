#include "pch.h"
#include "CNormalDistribution.h"


CNormalDistribution::CNormalDistribution()
{

}

CNormalDistribution::~CNormalDistribution()
{

}

float CNormalDistribution::RandNormFt()
{
	float sum = CRandom::RandFt() + CRandom::RandFt() + CRandom::RandFt();
	return sum / 3.0f;
}

float CNormalDistribution::RandNormFt(float min, float max)
{
	float range = (max - min) / 2.0f;
	return (RandNormFt() + 1) * range + min;
}

int CNormalDistribution::RandNormInt(int min, int max)
{
	return (int)RandNormFt(min, max);
}
