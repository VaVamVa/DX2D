#include "Framework.h"

Random::Random()
    : generator(randomDevice()), disInt(0, MAX_NUMBER),
    disFloat(0.0f, 1.0f)
{    
}

Random::~Random()
{
}

int Random::Range(const int& min, const int& max)
{
    return disInt(generator) % (max - min) + min;
}

float Random::Range(const float& min, const float& max)
{
    return (max - min) * disFloat(generator) + min;
}
