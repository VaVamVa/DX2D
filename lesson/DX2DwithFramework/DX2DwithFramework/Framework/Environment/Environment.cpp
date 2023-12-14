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
	// 정규화 된 3차원 공간을 viewPort의 크기 만큼 2차원으로 변환하여 화면에 출력한다.
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
	projectionBuffer = new MatrixBuffer();  // "투영"

	// 2D용 직육면체 투영용 절두체
	// LH : left hand coordination (왼손 xyz 좌표계)
	Matrix orthographic = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT,
		-1.0f, 1.0f
	);

	projectionBuffer->Set(orthographic);

	viewBuffer->SetVS(1);
	projectionBuffer->SetVS(2);
}
