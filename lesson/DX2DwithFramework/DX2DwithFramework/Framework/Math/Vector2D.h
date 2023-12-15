#pragma once

struct Vector2D : public Float2
{
	Vector2D() : Float2(0, 0) {}
	Vector2D(float x, float y) : Float2(x, y) {}
	
	operator Float2()
	{
		return { x, y };
	}

	Vector2D operator+(const Vector2D& rValue) const
	{
		return Vector2D(this->x + rValue.x, this->y + rValue.y);
	}
	void operator+=(const Vector2D& rValue)
	{
		x += rValue.x;
		y += rValue.y;
	}

	Vector2D operator-(const Vector2D& rValue) const
	{
		return Vector2D(this->x - rValue.x, this->y - rValue.y);
	}
	void operator-=(const Vector2D& rValue)
	{
		x -= rValue.x;
		y -= rValue.y;
	}

	Vector2D operator*(const float& scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}
	void operator*=(const float& scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	Vector2D operator/(const float& scalar)
	{
		return Vector2D(x / scalar, y / scalar);
	}
	void operator/=(const float& scalar)
	{
		x /= -scalar;
		y /= scalar;
	}

	bool operator==(const Vector2D other)
	{
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Vector2D other)
	{
		return (x != other.x || y != other.y);
	}

	float Length() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	Vector2D GetNormalized() const
	{
		float length = Length();
		return Vector2D(x / length, y / length);
	}
	void Normalized()
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