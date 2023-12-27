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
    if (walls[0]->GetCollider()->IsCircleCollision(ball->GetCollider()))
        ball->SetVelocity({ -nextVelocity.x, nextVelocity.y });
}
