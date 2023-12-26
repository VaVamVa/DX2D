#pragma once

namespace GameMath
{
    enum class Direction
    {
        UP, DOWN, RIGHT, LEFT, NONE
    };

    float Distance(const Vector2& v1, const Vector2& v2);

    float Clamp(const float& value, const float& min, const float& max);

    float Dot(const Vector2& v1, const Vector2& v2);

    Vector2 RandomPos(const float& min, const float& max);
}