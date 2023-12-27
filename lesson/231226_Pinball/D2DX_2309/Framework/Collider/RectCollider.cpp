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
    ObbDesc obb = GetObb();

    Vector2 direction = obb.position - collider->GetGlobalPos();

    float x = abs(Dot(direction, obb.axis[0]));
    float y = abs(Dot(direction, obb.axis[1]));

    if (x > obb.halfSize.x + collider->Radius()) return false;
    if (y > obb.halfSize.y + collider->Radius()) return false;

    if (x < obb.halfSize.x) return true;
    if (y < obb.halfSize.y) return true;

    Vector2 temp = Vector2(x, y) - obb.halfSize;

    return collider->Radius() > temp.Length();
}

bool RectCollider::IsRectCollision(RectCollider* collider)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = collider->GetObb();

    FOR(2)
    {
        if (IsSeperate(obbA.axis[i], obbA, obbB)) return false;
        if (IsSeperate(obbB.axis[i], obbA, obbB)) return false;
    }

    return true;
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

RectCollider::ObbDesc RectCollider::GetObb()
{
    ObbDesc obbDesc;
    obbDesc.position = GetGlobalPos();
    obbDesc.halfSize = Half();

    obbDesc.axis[0] = GetRight();
    obbDesc.axis[1] = GetUp();

    return obbDesc;
}

bool RectCollider::IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2)
{
    float d = abs(Dot(seperateAxis, box1.position - box2.position));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float a = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    return d > (a + b);
}
