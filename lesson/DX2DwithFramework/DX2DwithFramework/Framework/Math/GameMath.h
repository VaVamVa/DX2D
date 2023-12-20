#pragma once

namespace GameMath
{
	enum class Direction
	{
		NORTH, SOUTH, WEST, EAST, NONE
	};

	float Distance(const Vector2D& v1, const Vector2D& v2);

	template<typename T>
	T Clamp(const T& value, const float& min, const T max)
	{
		if (value < min)
			return min;

		if (value > max)
			return max;

		return value;
	}

	// ³»Àû
	float Dot(const Vector2D& v1, const Vector2D& v2);
}