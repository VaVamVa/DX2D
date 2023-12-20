#include "Framework.h"
#include "PlaneScene.h"

PlaneScene::PlaneScene()
{
    OBJ->Add(new Plane());

    CreateBG();
}

PlaneScene::~PlaneScene()
{
}

void PlaneScene::Update()
{
}

void PlaneScene::Render()
{
}

void PlaneScene::PostRender()
{
}

void PlaneScene::CreateBG()
{
    float scale = 0.3f;

    GameObject* bg = OBJ->Add(new Quad(path + L"bg.png", 4));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(path + L"bg2.png", 3));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(path + L"bg3.png", 2));
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
    bg = OBJ->Add(new Quad(path + L"bgBack.png", 1));    
    bg->SetPos(CENTER_X, CENTER_Y);
    bg->SetScale(scale, scale);
    bg->UpdateWorld();
}
