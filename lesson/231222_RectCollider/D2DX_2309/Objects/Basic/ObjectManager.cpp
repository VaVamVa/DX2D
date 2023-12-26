#include "Framework.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
    for (pair<int, GameObject*> object : objects)
        delete object.second;
}

void ObjectManager::Update()
{
    for (pair<int, GameObject*> object : objects)
        object.second->Update();
}

void ObjectManager::Render()
{
    for (pair<int, GameObject*> object : objects)
        object.second->Render();
}

void ObjectManager::PostRender()
{
    for (pair<int, GameObject*> object : objects)
        object.second->GUIRender();
}

GameObject* ObjectManager::Add(GameObject* object)
{
    objects.insert({ object->GetDepth(), object });

    return object;
}
