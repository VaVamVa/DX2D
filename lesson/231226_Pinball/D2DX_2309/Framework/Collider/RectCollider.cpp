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

GameMath::Direction RectCollider::GetDirection(const Vector2& point)
{
    Vector2 directionVector = (point - GetGlobalPos()).GetNormalized();
    Vector2 leftTopVector = (LeftTop() - GetGlobalPos()).GetNormalized();
    Vector2 rightTopVector = (RightTop() - GetGlobalPos()).GetNormalized();

    // 좌우 (두 외적 값이 같다)
    if (Cross(leftTopVector, directionVector) * Cross(rightTopVector, directionVector) > 0)
    {
        float rightAngle = abs(acosf(Dot(GetRight(), directionVector)));
        float leftAngle = abs(acosf(Dot(GetLeft(), directionVector)));
        //위의 두 내각을 비교하여 작은 쪽에 존재.
        return rightAngle < leftAngle ? Direction::RIGHT : Direction::LEFT;
    }
    // 상하 (두 외적 값이 다르다.)
    else if (Cross(leftTopVector, directionVector) * Cross(rightTopVector, directionVector) < 0)
    {
        float upAngle = abs(acosf(Dot(GetUp(), directionVector)));
        float downAngle = abs(acosf(Dot(GetDown(), directionVector)));
        //위의 두 내각을 비교하여 작은 쪽에 존재.
        return upAngle < downAngle ? Direction::UP : Direction::DOWN;
    }

    return Direction::NONE;
}

Vector2 RectCollider::LeftTop()
{
    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;

    return edge * world;
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
