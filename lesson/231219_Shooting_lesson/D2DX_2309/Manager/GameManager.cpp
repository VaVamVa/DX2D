#include "Framework.h"

//#include "Scenes/TutorialScene.h"
//#include "Scenes/SRTScene.h"
//#include "Scenes/PlaneScene.h"
#include "Scenes/CollisionScene.h"

GameManager::GameManager()
{
    Environment::Get();
    Keyboard::Get();
    Timer::Get();
    Random::Get();

    //scene = new TutorialScene();
    //scene = new SRTScene();
    scene = new CollisionScene();
}

GameManager::~GameManager()
{
    delete scene;

    Device::Delete();
    Environment::Delete();
    Keyboard::Delete();
    Timer::Delete();
    ObjectManager::Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();

    scene->Update();
    Collider::TotalUpdate();

    ObjectManager::Get()->Update();
}

void GameManager::Render()
{
    Device::Get()->Clear();

    ObjectManager::Get()->Render();
    scene->Render();
    Collider::TotalRender();
    scene->PostRender();

    Device::Get()->Present();
}
