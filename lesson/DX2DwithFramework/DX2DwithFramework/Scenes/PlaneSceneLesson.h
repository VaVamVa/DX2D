#pragma once

#include "Objects/PlaneLesson/PlaneL.h"
#include "Objects/PlaneLesson/BulletManager.h"
#include "Objects/PlaneLesson/EnemyManager.h"

class PlaneSceneLesson : public Scene
{
public:
	PlaneSceneLesson();
	~PlaneSceneLesson();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Plane* plane;

};
