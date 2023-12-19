#pragma once

#include "Objects/PlaneLesson/PlaneL.h"
#include "Objects/PlaneLesson/BulletManager.h"
#include "Objects/PlaneLesson/EnemyManager.h"

class PlaneSceneLesson : public Scene
{
public:
	PlaneSceneLesson();
	~PlaneSceneLesson();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	static void GetScore(int increasing = 1);

private:
	Plane* plane;
	static int score;
};
