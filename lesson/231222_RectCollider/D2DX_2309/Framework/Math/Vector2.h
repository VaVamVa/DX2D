#pragma once

struct Vector2 : public Float2
{
    Vector2() : Float2(0, 0) {};
    Vector2(float x, float y) : Float2(x, y)
    {}        

    operator Float2()
    {
        return { x, y };
    }

    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(x + v.x, y + v.y);
    }    
    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator*(const Vector2& v) const
    {
        return Vector2(x * v.x, y * v.y);
    }
    Vector2 operator/(const Vector2& v) const
    {
        return Vector2(x / v.x, y / v.y);
    }

    Vector2 operator*(const float& s) const
    {
        return Vector2(x * s, y * s);
    }
    Vector2 operator/(const float& s) const
    {
        return Vector2(x / s, y / s);
    }

    void operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
    }    
    void operator-=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
    }
    void operator*=(const float& s)
    {
        x *= s;
        y *= s;
    }
    void operator/=(const float& s)
    {
        x /= s;
        y /= s;
    }

    bool operator==(const Vector2& v)
    {
        if (x == v.x && y == v.y)
            return true;
        return false;
    }
    bool operator!=(const Vector2& v)
    {
        if (x == v.x && y == v.y)
            return false;
        return true;
    }

    Vector2 operator* (const Matrix& matrix) const
    {
        Float2 coord(x, y);
        XMVECTOR temp = XMLoadFloat2(&coord);

        temp = XMVector2TransformCoord(temp, matrix);

        XMStoreFloat2(&coord, temp);

        return Vector2(coord.x, coord.y);
    }

    void operator*= (const Matrix& matrix)
    {
        Vector2 result = Vector2(x, y) * matrix;
        x = result.x;
        y = result.y;
    }

    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    Vector2 GetNormalized() const
    {
        float length = Length();

        return Vector2(x / length, y / length);
    }

    void Normalize()
    {
        float length = Length();

        x /= length;
        y /= length;
    }

    float Angle()
    {
        return atan2(y, x);
    }
};