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

float GameMath::Dot(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2 GameMath::RandomPos(const float& min, const float& max)
{
    return Vector2(Random::Get()->Range(min, max),
        Random::Get()->Range(min, max));
}
