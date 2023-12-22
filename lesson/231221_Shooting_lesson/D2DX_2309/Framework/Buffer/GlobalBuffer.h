#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
    MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
    {
        matrix = XMMatrixIdentity();
    }

    void Set(Matrix value)
    {
        matrix = XMMatrixTranspose(value);
    }

private:
    Matrix matrix;
};

class ColorBuffer : public ConstBuffer
{
public:
    ColorBuffer() : ConstBuffer(&color, sizeof(Matrix))
    {
    }

    void Set(float r, float g, float b, float a = 1.0f)
    {
        color = { r, g, b, a };
    }

private:
    Float4 color = { 1, 1, 1, 1 };
};

class ValueBuffer : public ConstBuffer
{
public:
    ValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
    {
    }

    float* GetData() { return values; }

private:
    float values[4];
};