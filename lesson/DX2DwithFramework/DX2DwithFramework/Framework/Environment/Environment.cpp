#include "Framework.h"

Environment::Environment()
{
	SetViewport();
	SetProjection();
}

Environment::~Environment()
{
	delete viewBuffer;
	delete projectionBuffer;
}

void Environment::SetViewport()
{
	D3D11_VIEWPORT viewPort = {};
	// ����ȭ �� 3���� ������ viewPort�� ũ�� ��ŭ 2�������� ��ȯ�Ͽ� ȭ�鿡 ����Ѵ�.
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);
}

void Environment::SetProjection()
{
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();  // "����"

	// 2D�� ������ü ������ ����ü
	// LH : left hand coordination (�޼� xyz ��ǥ��)
	Matrix orthographic = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT,
		-1.0f, 1.0f
	);

	projectionBuffer->Set(orthographic);

	viewBuffer->SetVS(1);
	projectionBuffer->SetVS(2);
}
