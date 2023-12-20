#pragma once

class TutorialScene : public Scene
{
public:
    TutorialScene();
    ~TutorialScene();
        
    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    MatrixBuffer* worldBuffer;    

    vector<Vertex> vertices;
    vector<UINT> indices;
};
