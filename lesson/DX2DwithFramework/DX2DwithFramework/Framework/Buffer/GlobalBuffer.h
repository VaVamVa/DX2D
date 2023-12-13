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