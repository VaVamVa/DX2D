#pragma once

#include "Objects/Plane/Plane.h"

class PlaneScene : public Scene
{
public:
	PlaneScene();
	~PlaneScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Plane* plane;
};