#include "Framework.h"
#include "PlaneSceneLesson.h"

PlaneSceneLesson::PlaneSceneLesson()
{
	plane = new PlaneL();
	BulletManager::Get();
}

PlaneSceneLesson::~PlaneSceneLesson()
{
	delete plane;
}

void PlaneSceneLesson::Update()
{
	plane->Update();

	BulletManager::Get()->Update();
}

void PlaneSceneLesson::Render()
{
	plane->Render();

	BulletManager::Get()->Render();
}

void PlaneSceneLesson::PostRender()
{
}
