#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
	{
		matrix = DirectX::XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		matrix = DirectX::XMMatrixTranspose(value);
	}

private:
	Matrix matrix;
};