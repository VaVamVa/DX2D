#include "Framework.h"

//#include "Scenes/TutorialScene.h"
//#include "Scenes/SRTScene.h"
#include "Scenes/PlaneScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/PinballScene.h"

GameManager::GameManager()
{
    Environment::Get();
    Keyboard::Get();
    Timer::Get();
    Random::Get();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);

    //scene = new TutorialScene();
    //scene = new SRTScene();
    //scene = new PlaneScene();
    //scene = new CollisionScene();
    scene = new PinballScene();
}

GameManager::~GameManager()
{
    delete scene;

    Device::Delete();
    Environment::Delete();
    Keyboard::Delete();
    Timer::Delete();
    ObjectManager::Delete();
    Random::Delete();
    Collider::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
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

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    ImGui::Text(fps.c_str());

    scene->PostRender();
    ObjectManager::Get()->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Device::Get()->Present();
}
