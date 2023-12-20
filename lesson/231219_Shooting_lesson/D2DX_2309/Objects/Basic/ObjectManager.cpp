#include "Framework.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
    for (GameObject* object : objects)
        delete object;
    for (pair<int, GameObject*> object : mapObjects)
    {
        pair<multimap<int, GameObject*>::iterator, multimap<int, GameObject*>::iterator> pair_iter = mapObjects.equal_range(object.first);
    }
}

void ObjectManager::Update()
{
    for (GameObject* object : objects)
        object->Update();
}

void ObjectManager::Render()
{
    for (GameObject* object : objects)
        object->Render();
}

GameObject* ObjectManager::Add(GameObject* object)
{
    objects.push_back(object);

    sort(objects.begin(), objects.end(), GameObject::CompareObject);
    //objects.sort()    

    return object;
}

GameObject* ObjectManager::MapAdd(GameObject* object)
{
    mapObjects.insert({ object->GetDepth(), object });
    return object;
}
