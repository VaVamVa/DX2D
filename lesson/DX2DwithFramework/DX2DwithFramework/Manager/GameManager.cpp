#include "framework.h"
#include "GameManager.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/SRTScene.h"
#include "Scenes/PlaneScene.h"

GameManager::GameManager()
{
	GameTimer::Get();
	V_KEY;

	Environment::Get();

	//scene = new TutorialScene();
	//scene = new SRTScene();
	scene = new PlaneScene();
}

GameManager::~GameManager()
{
	delete scene;

	Environment::Delete();
	Device::Delete();
}

void GameManager::Update()
{
	V_KEY->Update();
	GameTimer::Get()->Update();

	scene->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	scene->Render();
	scene->PostRender();

	Device::Get()->Present();
}
