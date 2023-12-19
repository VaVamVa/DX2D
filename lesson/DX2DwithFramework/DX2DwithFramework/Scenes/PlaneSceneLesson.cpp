#include "Framework.h"
#include "PlaneSceneLesson.h"

PlaneSceneLesson::PlaneSceneLesson()
{
	plane = new Plane();
	BulletManager::Get();
	EnemyManager::Get()->SetTarget(plane);
	EnemyManager::Get()->ChangeStage(1);
}

PlaneSceneLesson::~PlaneSceneLesson()
{
	delete plane;
	BulletManager::Delete();
	EnemyManager::Delete();
	VertexShader::Destroy();
	PixelShader::Destroy();
}

void PlaneSceneLesson::Update()
{
	plane->Update();

	BulletManager::Get()->Update();
	EnemyManager::Get()->Update();
}

void PlaneSceneLesson::Render()
{
	plane->Render();

	BulletManager::Get()->Render();
	EnemyManager::Get()->Render();
}

void PlaneSceneLesson::PostRender()
{
}
