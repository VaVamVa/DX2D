#include "Framework.h"
#include "GameMath.h"

float GameMath::Distance(const Vector2& v1, const Vector2& v2)
{
    return (v2 - v1).Length();
}

float GameMath::Clamp(const float& value, const float& min, const float& max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}