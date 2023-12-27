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
            nextVelocity += rightFlipper->collider->GetUp();
            ball->Translate(nextVelocity * DELTA * POWER);
            nextVelocity *= rightFlipper->interpolationValue * POWER;
        }
        else
        {
            nextVelocity = rightFlipper->collider->GetRight() * ball->GetVelocity();
        }
    }
    if (leftFlipper->collider->IsCircleCollision(ball->GetCollider()))
    {
        isCollision = true;
        if (isSwing = leftFlipper->isSwing)
        {
            nextVelocity += leftFlipper->collider->GetUp();
            nextVelocity.x *= -1.0f;
            ball->Translate(nextVelocity * DELTA * POWER);
            nextVelocity *= leftFlipper->interpolationValue * POWER;
        }
        else
        {
            nextVelocity = leftFlipper->collider->GetRight() * ball->GetVelocity();
        }
    }

    if (isCollision)
    {
        ball->SetVelocity(nextVelocity);
        return true;
    }

    return false;
}
