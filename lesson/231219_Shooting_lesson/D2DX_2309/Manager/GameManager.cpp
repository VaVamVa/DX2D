#include "Framework.h"

//#include "Scenes/TutorialScene.h"
//#include "Scenes/SRTScene.h"
#include "Scenes/PlaneScene.h"

GameManager::GameManager()
{
    Environment::Get();
    Keyboard::Get();
    Timer::Get();

    //scene = new TutorialScene();
    //scene = new SRTScene();
    scene = new PlaneScene();
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
    ObjectManager::Get()->Update();
}

void GameManager::Render()
{
    Device::Get()->Clear();

    ObjectManager::Get()->Render();
    scene->Render();
    scene->PostRender();

    Device::Get()->Present();
}
