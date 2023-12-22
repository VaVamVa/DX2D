#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size)
{
    type = Type::RECT;

    Vector2 halfSize = size * 0.5f;

    vertices.emplace_back(-halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, +halfSize.y);

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}

bool RectCollider::IsPointCollision(const Vector2& point)
{
    Matrix invWorld = XMMatrixInverse(nullptr, world);

    Vector2 temp = point * invWorld;

    Vector2 half = size * 0.5f;

    return abs(temp.x) < half.x && abs(temp.y) < half.y;
}

bool RectCollider::IsCircleCollision(CircleCollider* collider)
{
    return false;
}

bool RectCollider::IsRectCollision(RectCollider* collider)
{
    return false;
}

Vector2 RectCollider::LeftTop()
{
    return Vector2();
}

Vector2 RectCollider::LeftBottom()
{
    return Vector2();
}

Vector2 RectCollider::RightTop()
{
    return Vector2();
}

Vector2 RectCollider::RightBottom()
{
    return Vector2();
}
