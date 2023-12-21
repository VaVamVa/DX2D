#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	colliders.push_back(new CircleCollider(100.0f));
	colliders.back()->SetPos(Vector2(CENTER_X, CENTER_Y));
}

CollisionScene::~CollisionScene()
{
	Collider::Delete();
}

void CollisionScene::Update()
{
	if (colliders[0]->IsPointCollision(mousePos))
	{
		colliders[0]->SetColor(1, 0, 0);
	}
	else
	{
		colliders[0]->SetColor(0, 1, 0);
	}
}

void CollisionScene::Render()
{
}

void CollisionScene::PostRender()
{
}
