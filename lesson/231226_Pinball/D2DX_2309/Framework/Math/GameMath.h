#pragma once

namespace GameMath
{
    enum class Direction
    {
        UP, DOWN, RIGHT, LEFT, NONE
    };

    float Distance(const Vector2& v1, const Vector2& v2);

    float Clamp(const float& min, const float& max, const float& value);

    float Dot(const Vector2& v1, const Vector2& v2);

    Vector2 RandomPos(const float& min, const float& max);

    float Lerp(const float& start, const float& end, float t);
    Vector2 Lerp(const Vector2& start, const Vector2& end, float t);
    Vector2 SLerp(const Vector2& start, const Vector2& end, float t);
}