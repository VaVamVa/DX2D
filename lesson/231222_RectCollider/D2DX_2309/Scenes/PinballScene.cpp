#include "Framework.h"
#include "PinballScene.h"

PinballScene::PinballScene()
{
	bg = (Quad*)OBJ->Add(new Quad(L"Textures/Pinball/Background.png"));
	bg->SetPos(CENTER);
	bg->SetScale(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) / bg->GetSize());
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
