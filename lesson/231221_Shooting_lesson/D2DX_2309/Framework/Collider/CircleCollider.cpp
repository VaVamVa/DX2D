#include "Framework.h"

CircleCollider::CircleCollider(float radius)
	: radius(radius)
{
	type = Type::CIRCLE;

	vertices.reserve(VERTEX_COUNT + 1);

	float step = XM_2PI / VERTEX_COUNT;
	for (UINT i = 0; i <= VERTEX_COUNT; i++)
	{
		float x = cos(step * i) * radius;
		float y = sin(step * i) * radius;

		vertices.emplace_back(x, y);
	}

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexPos), vertices.size());
}

bool CircleCollider::IsCircleCollision(CircleCollider* collider)
{
	float distance = Distance(collider->GetGlobalPos(), GetGlobalPos());

	return distance < Radius() + collider->Radius();
}

bool CircleCollider::IsPointCollision(const Vector2& point)
{
	float distance = Distance(point, GetGlobalPos());

	return distance < Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* collider)
{
	return false;
}
