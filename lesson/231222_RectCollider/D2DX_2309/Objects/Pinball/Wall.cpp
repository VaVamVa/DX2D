#include "Framework.h"
#include "Wall.h"

Wall::Wall(int index)
	:Quad(L"Textures/Pinball/Wall.png", 0)
{
	tag = "Wall" + to_string(index);
	Load();

	collider = new RectCollider(GetSize());
	collider->SetTag(tag + "_Collider");
	collider->SetParent(this);
	collider->Load();

	UpdateWorld();
}
