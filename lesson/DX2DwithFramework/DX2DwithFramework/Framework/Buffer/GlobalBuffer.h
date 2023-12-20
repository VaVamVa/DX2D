#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
	{
		matrix = DirectX::XMMatrixIdentity();  // 단위 행렬(항등 행렬)로 초기화
	}

	void Set(Matrix value)
	{
		matrix = DirectX::XMMatrixTranspose(value);  // 전치 행렬로 바꿔줌
	}

private:
	Matrix matrix;
};

class ColorBuffer : public ConstBuffer
{
public:
	ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
	{}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		color = { r, g, b, a };
	}

private:
	Float4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
};