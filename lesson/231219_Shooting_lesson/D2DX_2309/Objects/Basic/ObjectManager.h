#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update();
	void Render();

	GameObject* Add(GameObject* object);
	GameObject* MapAdd(GameObject* object);

private:
	vector<GameObject*> objects;
	multimap<int, GameObject*> mapObjects;
};