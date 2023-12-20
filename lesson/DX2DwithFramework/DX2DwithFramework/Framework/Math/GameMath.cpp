#include "Framework.h"

float GameMath::Distance(const Vector2D& v1, const Vector2D& v2)
{
    return (v2 - v1).Length();
}

/*
schalr ��ȯ�ϴ� ���ͳ����� �� (��� ��_dot ���� ǥ��)
A@B = abs(A) * abs(B) * cos(angle_A���Ϳ� B���Ͱ� �̷�� ��)
    = A.x * B.x + A.y * B.y
*/
float GameMath::Dot(const Vector2D& v1, const Vector2D& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}