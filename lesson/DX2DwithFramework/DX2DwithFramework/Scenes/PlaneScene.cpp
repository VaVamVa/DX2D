#include "Framework.h"
#include "PlaneScene.h"
#include "Objects/Plane/BulletManager.h"

PlaneScene::PlaneScene()
{
	plane = new Plane();
	BulletManager::Get();
}

PlaneScene::~PlaneScene()
{
	delete plane;
	BulletManager::Delete();
}

void PlaneScene::Update()
{
	plane->Update();
	BulletManager::Get()->Update();
}

void PlaneScene::Render()
{
	plane->Render();
	BulletManager::Get()->Render();
}

void PlaneScene::PostRender()
{
}
