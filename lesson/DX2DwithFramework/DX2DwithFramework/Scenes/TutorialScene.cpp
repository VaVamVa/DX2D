#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");


	UINT count = 50;
	Float2 center = { CENTER_X, CENTER_Y };
	float radius = 100.0f;
	
	float stepAngle = DirectX::XM_2PI / count;
	float angle = DirectX::XM_PIDIV2;

	vertices.emplace_back(center.x, center.y, 1, 1, 1);
	vertices.emplace_back(center.x + radius * cos(angle), center.y + radius * sin(angle), 0, 1, 1);

	FOR(i, 0, count)
	{
		angle -= stepAngle;

		vertices.emplace_back(center.x + radius * cos(angle), center.y + radius * sin(angle), 0, 1, 1);

		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();

}

TutorialScene::~TutorialScene()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;

	delete worldBuffer;

	indices.clear();
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
	worldBuffer->SetVS(0);

	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TutorialScene::PostRender()
{
}
