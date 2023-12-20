#pragma once

struct VertexColor
{
    Float3 pos = {};
    Float4 color = {};

    VertexColor(float x, float y)
        :pos(x, y, 0.0f) {}

    VertexColor(float x, float y, float r, float g, float b)
        :pos(x, y, 0.0f), color(r, g, b, 1.0f) {}
};

struct VertexPos
{
    Float3 pos = {};

    VertexPos(float x, float y)
        : pos(x, y, 0.0f) {}
};

struct VertexUV
{
    Float3 pos = {};
    Float2 uv = {};

    VertexUV(float x, float y)
        :pos(x, y, 0.0f) {}

    VertexUV(float x, float y, float u, float v)
        :pos(x, y, 0.0f), uv(u, v) {}
};