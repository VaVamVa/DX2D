#include "Framework.h"
#include "GameMath.h"

float GameMath::Distance(const Vector2& v1, const Vector2& v2)
{
    return (v2 - v1).Length();
}

float GameMath::Clamp(const float& min, const float& max, const float& value)
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

float GameMath::Lerp(const float& start, const float& end, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return start + (end - start) * t;
}

Vector2 GameMath::Lerp(const Vector2& start, const Vector2& end, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return start + (end - start) * t;
}

Vector2 GameMath::SLerp(const Vector2& start, const Vector2& end, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return start + (end - start) * (t * t);
}
