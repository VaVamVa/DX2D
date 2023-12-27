#include "Framework.h"

#include "Objects/Pinball/Wall.h"
#include "Objects/Pinball/Ball.h"
#include "WallManager.h"

WallManager::WallManager()
{
    walls.reserve(POOL_SIZE);
    walls.push_back(new Wall(0));
    walls.push_back(new Wall(1));
    walls.push_back(new Wall(2));
}

WallManager::~WallManager()
{
    walls.clear();
}

void WallManager::Render()
{
    for (Wall* wall : walls)
    {
        wall->Render();
    }
}

bool WallManager::IsCollision(Ball* ball)
{
    Vector2 nextVelocity = ball->GetVelocity();
    float radius = ball->GetSize().x * ball->GetCollider()->GetScale().x * 0.5f;
    float depth = walls[0]->GetSize().y * walls[0]->GetScale().y * 0.5f;
    if (walls[0]->GetCollider()->IsCircleCollision(ball->GetCollider()))
    {
        nextVelocity.x *= -1.0f;
        float overlap = ball->GetPos().x + radius - (walls[0]->GetPos().x - depth);
        if (overlap > 0) ball->Translate(-overlap, 0.0f);
    }
    if (walls[1]->GetCollider()->IsCircleCollision(ball->GetCollider()))
    {
        nextVelocity.x *= -1.0f;
        float overlap = walls[1]->GetPos().x + depth - (ball->GetPos().x - radius);
        if (overlap > 0) ball->Translate(overlap, 0.0f);
    }
    if (walls[2]->GetCollider()->IsCircleCollision(ball->GetCollider()))
    {
        nextVelocity.y *= -1.0f;
        float overlap = ball->GetPos().y + radius - (walls[2]->GetPos().y - depth);
        if (overlap > 0) ball->Translate(0.0f, -overlap);
    }

    if (nextVelocity != ball->GetVelocity())
    {
        ball->SetVelocity(nextVelocity);
        
        return true;
    }

    return false;
}
