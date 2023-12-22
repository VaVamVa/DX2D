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
    ObbDesc obb = GetObbDesc();

    Vector2 direction = obb.position - collider->GetGlobalPos();

    float dotX = abs(Dot(direction, obb.axis[0]));
    float dotY = abs(Dot(direction, obb.axis[1]));

    if (dotX > collider->Radius() + obb.halfSize.x)
        return false;
    if (dotY > collider->Radius() + obb.halfSize.y)
        return false;

    if (dotX < obb.halfSize.x) return true;
    if (dotY < obb.halfSize.y) return true;

    float shortestDistance = (Vector2(dotX, dotY) - obb.halfSize).Length();

    return collider->Radius() > shortestDistance;
}

/*
OBB 사각형 충돌
분리축 이론에 기반.
    - 평행한 선분들이 하나의 축을 이루게 된다.
    - 직사각형은 두개의 축을 가짐.

*/
bool RectCollider::IsRectCollision(RectCollider* collider)
{
    ObbDesc obbA = GetObbDesc();
    ObbDesc obbB = collider->GetObbDesc();

    FOR(2)
    {
        if (IsSeperate(obbA.axis[i], obbA, obbB))
            return false;
        if (IsSeperate(obbB.axis[i], obbA, obbB))
            return false;
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

RectCollider::ObbDesc RectCollider::GetObbDesc()
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

    return d > (a + b);  // 떨어져 있다 = true
}

