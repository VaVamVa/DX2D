#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Update();
	void Render();
	void PostRender();

	GameObject* Add(GameObject* object);

private:
	multimap<int, GameObject*> objects;
};