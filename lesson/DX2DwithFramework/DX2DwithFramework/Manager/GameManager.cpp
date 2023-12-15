#include "framework.h"
#include "GameManager.h"

#include "Scenes/PlaneSceneLesson.h"

GameManager::GameManager()
{
	GameTimer::Get();
	V_KEY;

	Environment::Get();

	//scene = new TutorialScene();
	//scene = new SRTScene();
	//scene = new PlaneScene();
	scene = new PlaneSceneLesson();
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
