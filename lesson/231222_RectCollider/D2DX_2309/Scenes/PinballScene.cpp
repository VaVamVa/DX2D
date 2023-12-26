#include "Framework.h"
#include "PinballScene.h"

PinballScene::PinballScene()
{
	GameObject* bg = OBJ->Add(new Quad(L"Textures/Pinball/Background.png"));
	bg->SetPos(CENTER);
	bg->SetScale(2, 2);
	bg->UpdateWorld();
}

PinballScene::~PinballScene()
{
}

void PinballScene::Update()
{
}

void PinballScene::Render()
{
}

void PinballScene::PostRender()
{
}
