#include "Framework.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
    for (GameObject* object : objects)
        delete object;
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
