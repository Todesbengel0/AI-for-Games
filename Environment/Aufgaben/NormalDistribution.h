#pragma once

class CNormalDistribution : public CRandom
{
public:
	CNormalDistribution();
	~CNormalDistribution();

public:
	float RandNormFt();
	float RandNormFt(float min, float max);
	int RandNormInt(int min, int max);
};
