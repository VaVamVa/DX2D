#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update();
	void Render();

	GameObject* Add(GameObject* object);

private:
	multimap<int, GameObject*> objects;
};