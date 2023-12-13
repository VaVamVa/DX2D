#include "framework.h"
#include "GameManager.h"

#include "Scenes/TutorialScene.h"

GameManager::GameManager()
{
	D3D11_VIEWPORT viewPort = {};
	// ����ȭ �� 3���� ������ viewPort�� ũ�� ��ŭ 2�������� ��ȯ�Ͽ� ȭ�鿡 ����Ѵ�.
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	scene = new TutorialScene();
}

GameManager::~GameManager()
{
	delete scene;

	Device::Delete();
}

void GameManager::Update()
{
	V_KEY->Update();

	scene->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	scene->Render();
	scene->PostRender();

	Device::Get()->Present();
}
