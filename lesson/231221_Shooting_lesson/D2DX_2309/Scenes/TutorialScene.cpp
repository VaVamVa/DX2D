#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
    pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");
    
    UINT count = 50;
    Float2 center = { CENTER_X, CENTER_Y };
    float radius = 200.0f;

    float stepAngle = XM_2PI / count;
    float angle = XM_PIDIV2;

    vertices.emplace_back(center.x, center.y, 1, 0, 0);
    vertices.emplace_back(center.x + cos(angle) * radius, center.y + sin(angle) * radius, 0, 0, 1);

    FOR(count)
    {
        angle -= stepAngle;

        vertices.emplace_back(center.x + cos(angle) * radius, center.y + sin(angle) * radius, 0, 0, 1);

        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }    

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(Vertex), vertices.size());

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
