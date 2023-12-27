#include "Framework.h"

#include "Objects/Pinball/Flipper.h"
#include "Objects/Pinball/Ball.h"
#include "FlipperManager.h"

FlipperManager::FlipperManager()
{
    rightFlipper = new Flipper(true);
    leftFlipper = new Flipper(false);
}

bool FlipperManager::IsCollision(Ball* ball)
{
    bool isCollision = false, isSwing = false;
    Vector2 nextVelocity = { 0.0f, 0.0f };
    if (rightFlipper->collider->IsCircleCollision(ball->GetCollider()))
    {
        isCollision = true;
        if (isSwing = rightFlipper->isSwing)
        {
            nextVelocity += rightFlipper->collider->GetUp().GetNormalized();
            nextVelocity *= rightFlipper->interpolationValue * POWER;
        }
    }
    if (leftFlipper->collider->IsCircleCollision(ball->GetCollider()))
    {
        isCollision = true;
        if (isSwing = leftFlipper->isSwing)
        {
            nextVelocity += leftFlipper->collider->GetUp().GetNormalized();
            nextVelocity.x *= -1.0f;
            nextVelocity *= leftFlipper->interpolationValue * POWER;
        }
    }

    if (isCollision)
    {
        ball->SetVelocity(nextVelocity);
        return true;
    }

    return false;
}
