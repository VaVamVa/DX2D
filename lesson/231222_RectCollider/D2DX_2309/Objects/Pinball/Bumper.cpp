#include "Framework.h"
#include "Bumper.h"

Bumper::Bumper(int index)
	:Quad(L"Textures/Pinball/Bumper1.png", 1)
{
	int tmp = index;
	while (tmp >= 0)
	{
		tag = "Bumper" + to_string(tmp);
		if (Load())
			break;
		tmp--;
	}
	OBJ->Add(this);

	colliders.resize(3);
	FOR(3)
	{
		colliders[i] = new RectCollider();
		string colliderTag = tag + "_Collider" + to_string(i);
		colliders[i]->SetTag(colliderTag);
		colliders[i]->SetParent(this);
		colliders[i]->Load();
	}

	tag = "Bumper" + to_string(index);
	FOR(3)
	{
		colliders[i]->SetTag(tag + "_Collider" + to_string(i));
	}
}

Vector2 Bumper::Repulse(Vector2 direction)
{
	return Vector2();
}

bool Bumper::IsCollision(Ball* ball)
{
	return false;
}
