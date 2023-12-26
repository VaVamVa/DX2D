#include "Framework.h"
#include "Bumper.h"

Bumper::Bumper()
	:Quad(L"Textures/Pinball/Bumper1.png")
{
	tag = "Bumper";
	Load();

	colliders.resize(3);
	FOR(3)
	{
		colliders[i] = new RectCollider();
		string colliderTag = "BumperCollider" + to_string(i);
		colliders[i]->SetTag(colliderTag);
		colliders[i]->SetParent(this);
		colliders[i]->Load();
	}
}
