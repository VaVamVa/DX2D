#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	//colliders.push_back(new CircleCollider(100));
	//colliders.back()->SetPos(CENTER);

	colliders.push_back(new RectCollider(Vector2(100, 200)));
	colliders.back()->SetPos(CENTER);
}

CollisionScene::~CollisionScene()
{
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
	for (Collider* collider : colliders)
		collider->GUIRender();
}
