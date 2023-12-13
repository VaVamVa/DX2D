#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
	pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

	vertices.emplace_back(0.0f, 0.0f, 1, 1, 1);

	UINT count = 3;
	Float2 center = { CENTER_X, CENTER_Y };
	float radius = 50.0f;
	
	float stepAngle = DirectX::XM_2PI / count;
	float angle = DirectX::XM_PIDIV2;
	vertices.emplace_back(radius * cos(angle) + center.x, radius * sin(angle) + center.y, 0, 0, 1);

	FOR(i, 0, count)
	{
		angle -= stepAngle;
		vertices.emplace_back(radius * cos(angle) + center.x, radius * sin(angle) + center.y, 0, 0, 1);

		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

	indexBuffer = new IndexBuffer(indices.data(), sizeof(indices));

	worldBuffer = new MatrixBuffer();
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();

	Matrix orthographic = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT,
		-1.0f, 1.0f
	);

	projectionBuffer->Set(orthographic);
}

TutorialScene::~TutorialScene()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexBuffer;
	delete indexBuffer;
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
	vertexBuffer->Set();
	indexBuffer->Set();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TutorialScene::PostRender()
{
}
