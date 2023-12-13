#include "framework.h"

Random::Random()
	:engine1(randDevice())
{
}

Random::~Random()
{
}

int Random::GetRandomInt(const int& min, const int& max)
{
	std::uniform_int_distribution<int> range(min, max);
	return range(engine1);
}

float Random::GetRandomFloat(const float& min, const float& max)
{
	std::uniform_real_distribution<float> range(0, 1);
	return (max - min) * range(engine1) + min;
}