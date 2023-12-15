#pragma once

#include "Objects/PlaneLesson/PlaneL.h"
#include "Objects/PlaneLesson/BulletManager.h"

class PlaneSceneLesson : public Scene
{
public:
	PlaneSceneLesson();
	~PlaneSceneLesson();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	PlaneL* plane;

};
