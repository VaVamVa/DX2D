#pragma once
//VertexLayouts

struct VertexPos//���� : 3���� ���������� �� ��
{
    XMFLOAT3 pos = {};

    VertexPos(float x, float y) : pos(x, y, 0)
    {
    }
};

struct Vertex
{
    XMFLOAT3 pos = {};
    XMFLOAT2 uv = {};

    Vertex(float x, float y) : pos(x, y, 0)
    {
    }

    Vertex(float x, float y, float u, float v)
        : pos(x, y, 0), uv(u, v)
    {
    }
};