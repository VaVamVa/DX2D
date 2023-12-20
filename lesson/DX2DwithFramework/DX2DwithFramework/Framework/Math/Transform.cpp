#include "Framework.h"

Transform::Transform()
{
	world = DirectX::XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
	S = DirectX::XMMatrixScaling(localScale.x, localScale.y, 1);
	// �� ��ȯ (y�� ��ȯ���� �ݴ�� ������ ���� ����!)
	// Roll : x, Pitch : y, Yaw : z
	R = DirectX::XMMatrixRotationRollPitchYaw(localRotation.x, localRotation.y, localRotation.z);
	T = DirectX::XMMatrixTranslation(localPosition.x, localPosition.y, 0);

	world = S * R * T;

	if (parent != nullptr)
		world += parent->world;

	DirectX::XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	DirectX::XMStoreFloat2(&globalPosition, outT);
	DirectX::XMStoreFloat2(&globalScale, outS);
}
