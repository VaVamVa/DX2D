#pragma once

struct Vertex
{
    Float3 pos = {};
    Float4 color = {};

    Vertex(float x, float y)
        :pos(x, y, 0.0f) {}

    Vertex(float x, float y, float r, float g, float b)
        :pos(x, y, 0.0f), color(r, g, b, 1) {}
};