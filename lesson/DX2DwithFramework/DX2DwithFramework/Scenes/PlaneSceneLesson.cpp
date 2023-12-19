#include "Framework.h"
#include "PlaneSceneLesson.h"

int PlaneSceneLesson::score = 0;

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

void PlaneSceneLesson::GetScore(int increasing)
{
	score += increasing;
	if (score == 6)
		EnemyManager::Get()->ChangeStage(3);
	else if (score == 3)
		EnemyManager::Get()->ChangeStage(2);
}
