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
    Collider::Delete();
}

void PlaneScene::Update()
{
    bgLight->Rotate(DELTA);
    bgLight->UpdateWorld();
    valueBuffer->GetDate()[0] = bgLight->GetAngle() - XM_PIDIV2;

    EnemyManager::Get()->Update();
    EnemyManager::Get()->IsCollision(plane->GetCollider());
}

void PlaneScene::Render()
{
    valueBuffer->SetPS(0);
    bgLightTexture->PSSet(1);
    bg2->Render();
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
    /*bg = OBJ->Add(new Quad(PATH + L"bg2.png", 3));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();*/
    /*bg = OBJ->Add(new Quad(PATH + L"bg3.png", 2));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();*/
    /*bg = OBJ->Add(new Quad(PATH + L"bgBack.png", 1));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();*/
    Quad* space = new Quad(PATH + L"space.png", 0);
    bg = OBJ->Add(space);
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) / space->GetSize());
    bg->UpdateWorld();


    bgLight = OBJ->Add(new Quad(PATH + L"bgLight.png", 5));
    bgLight->SetPos(CENTER_X, CENTER_Y);
    bgLight->SetScale(scale, scale);

    bg2 = new Quad(PATH + L"bg2.png", 6);
    bg2->SetPos(CENTER_X, CENTER_Y);
    bg2->SetScale(scale, scale);
    bg2->SetPS(L"PixelBGLight.hlsl");
    bg2->UpdateWorld();

    bgLightTexture = Texture::Add(PATH + L"bgLight.png");

    valueBuffer = new ValueBuffer();
}
