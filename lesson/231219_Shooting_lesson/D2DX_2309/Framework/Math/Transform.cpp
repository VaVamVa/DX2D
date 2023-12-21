#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
    S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
    R = XMMatrixRotationRollPitchYaw(localRotation.x, localRotation.y, localRotation.z);
    T = XMMatrixTranslation(localPosition.x, localPosition.y, 0);

    world = S * R * T;

    if (parent)
        world *= parent->world;

    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    XMStoreFloat2(&globalPosition, outT);
    XMStoreFloat2(&globalScale, outS);
}

bool Transform::IsActive()
{
    if (parent == nullptr)
        return isActive;

    if (!isActive)
        return false;

    return parent->IsActive();
}
