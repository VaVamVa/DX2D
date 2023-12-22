#pragma once

class Quad : public GameObject
{
public:
    Quad(Vector2 size);
    Quad(wstring textureFile, int depth = 0);
    ~Quad();
        
    virtual void Update() override {}
    virtual void Render() override;

    Vector2 GetSize() { return size; }
private:
    void Create();

private:
    Vector2 size;    

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    vector<Vertex> vertices;
    vector<UINT> indices;

    Texture* texture = nullptr;
};