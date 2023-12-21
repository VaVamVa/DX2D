#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = Type::RECT;

    Vector2 halfSize = size * 0.5f;

    vertices.emplace_back(-halfSize.x, halfSize.y);

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

RectCollider::~RectCollider()
{
}

bool RectCollider::IsPointCollision(const Vector2 point)
{
    return false;
}

bool RectCollider::IsCircleCollision(CircleCollider* collider)
{
    return false;
}

bool RectCollider::IsRectCollision(RectCollider* collider)
{
    return false;
}
