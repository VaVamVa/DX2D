#include "Framework.h"
#include "PlaneScene.h"

PlaneScene::PlaneScene()
{
	plane = new Plane();
}

PlaneScene::~PlaneScene()
{
	delete plane;
}

void PlaneScene::Update()
{
	plane->Update();
}

void PlaneScene::Render()
{
	plane->Render();
}

void PlaneScene::PostRender()
{
}
