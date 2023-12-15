#include "Framework.h"

Environment::Environment()
{
	SetViewport();
	SetProjection();

	CreateSamplerState();
	CreateBlendState();
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

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	// Ȯ�� ��� ó�� (LINEAR -> ���� ������������ ������ ��ȭ)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	// uv ���� 1�� �Ѿ�� ���� �̹����� ��µǹǷ�,
	// uv ���� 1�� �Ѿ �� ��� ó���� ���ΰ�.
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;

	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	
	//LOD(Level Of Detail) : ī�޶��� �Ÿ��� ���� ����Ƽ�� �ٸ��� �ϴ� ��
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};

	blendDesc.RenderTarget[0].BlendEnable = true;

	// Src : ����� ����, Dest : ����� �޹�� ����
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // Inverse Alpha = 1 - ALPHA

	// ���� ó���� ������� ��� �� ���ΰ�.
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &blendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}
