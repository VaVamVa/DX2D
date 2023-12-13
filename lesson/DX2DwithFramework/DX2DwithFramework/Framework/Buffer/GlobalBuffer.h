#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
	{
		matrix = DirectX::XMMatrixIdentity();  // ���� ���(�׵� ���)�� �ʱ�ȭ
	}

	void Set(Matrix value)
	{
		matrix = DirectX::XMMatrixTranspose(value);  // ��ġ ��ķ� �ٲ���
	}

private:
	Matrix matrix;
};