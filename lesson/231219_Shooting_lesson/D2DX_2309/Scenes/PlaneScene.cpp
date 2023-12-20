#include "Framework.h"
#include "PlaneScene.h"

#include "Objects/ShootingGame/Plane.h"
#include "Objects/ShootingGame/EnemyManager.h"
#include "Objects/ShootingGame/BulletManager.h"

PlaneScene::PlaneScene()
{
    plane = (Plane*)OBJ->Add(new Plane());
    BulletManager::Get();
    EnemyManager::Get()->CreateEnemies(plane);

    CreateBG();
}

PlaneScene::~PlaneScene()
{
}

void PlaneScene::Update()
{
    EnemyManager::Get()->Update();
    EnemyManager::Get()->Collision(plane->GetCollider());
}

void PlaneScene::Render()
{
}

void PlaneScene::PostRender()
{
}

void PlaneScene::CreateBG()
{
    float scale = 0.4f;

    GameObject* bg = OBJ->Add(new Quad(PATH + L"bg.png", 4));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(PATH + L"bg2.png", 3));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(PATH + L"bg3.png", 2));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(PATH + L"bgBack.png", 1));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    Quad* space = new Quad(PATH + L"space.png", 0);
    bg = OBJ->Add(space);
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) / space->GetSize());
    bg->UpdateWorld();
}
