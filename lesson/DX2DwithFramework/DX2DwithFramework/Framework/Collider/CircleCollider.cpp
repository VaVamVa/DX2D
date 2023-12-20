#include "Framework.h"

CircleCollider::CircleCollider(float radius)
    :radius(radius)
{
    vertices.reserve(VERTEX_COUNT + 1);
    float step = DirectX::XM_2PI / VERTEX_COUNT;

    FOR(i, 0, VERTEX_COUNT + 1)
    {
        float x = cos(step * i) * radius;
        float y = sin(step * i) * radius;

        vertices.emplace_back(x, y);
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

bool CircleCollider::IsCollision(Collider* collider)
{
    CircleCollider* circleDetector = dynamic_cast<CircleCollider*>(collider);
    if (circleDetector != nullptr)
        return IsCircleCollision(circleDetector);
}

bool CircleCollider::IsCircleCollision(CircleCollider* collider)
{
    float distance = GameMath::Distance(collider->GetGlobalPos(), GetGlobalPos());

    return distance < Radius();
}
