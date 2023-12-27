#include "Framework.h"
#include "Bumper.h"

Bumper::Bumper() : Quad(L"Textures/Pinball/Bumper.png")
{
	tag = "Bumper";
	Load();
		
	colliders.resize(3);
	FOR(3)
	{
		colliders[i] = new RectCollider();
		string tag = "BumperCollider" + to_string(i);
		colliders[i]->SetTag(tag);
		colliders[i]->SetParent(this);
		colliders[i]->Load();
	}
}
