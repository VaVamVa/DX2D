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

/*
schalr 반환하는 벡터끼리의 곱 (가운데 점_dot 으로 표현)
A@B = abs(A) * abs(B) * cos(angle_A벡터와 B벡터가 이루는 각)
    = A.x * B.x + A.y * B.y
*/
float GameMath::Dot(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2 GameMath::RandomPos(const float& min, const float& max)
{
    return Vector2(Random::Get()->Range(min, max), Random::Get()->Range(min, max));
}
