#include "Framework.h"

#include "Objects/Pinball/Ball.h"
#include "Objects/Pinball/Bumper.h"

#include "BumperManager.h"

BumperManager::BumperManager()
{
    bumpers.reserve(POOL_SIZE);
}

BumperManager::~BumperManager()
{
    bumpers.clear();
}

void BumperManager::CreateNewBumper(int count)
{
    FOR(count)
    {
        bool flag = true;
        for (Bumper* bumper : bumpers)
        {
            if (!bumper->IsActive())
            {
                bumper->SetActive(true);
                flag = false;
                break;
            }
        }
        if (flag && bumpers.size() < POOL_SIZE)
            bumpers.push_back(new Bumper(bumpers.size() + i));
    }
}

void BumperManager::DeactivateBumper(int count)
{
    FOR(count)
    {
        for (int j = bumpers.size() - 1; j >= 0; j--)
        {
            if (bumpers[j]->IsActive())
            {
                bumpers[j]->SetActive(false);
                return;
            }
        }
    }
}

bool BumperManager::IsCollision(Ball* ball)
{
    for (Bumper* bumper : bumpers)
    {
        if (bumper->IsActive() && bumper->IsCollision(ball))
        {
            //Vector2 nextDirection = bumper->Repulse(ball->GetVelocity());
            //ball->SetVelocity(nextDirection);
            return true;
        }
    }
    return false;
}

void BumperManager::GUIRender()
{
    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        ImGui::Text(tag.c_str());


        if (ImGui::Button("-"))
            DeactivateBumper();

        ImGui::SameLine();

        if (ImGui::Button("+"))
            CreateNewBumper();
        
        ImGui::TreePop();
    }
}
