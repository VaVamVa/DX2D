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

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	// 확대 축소 처리 (LINEAR -> 색상 선형보간으로 엘리싱 완화)
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	// uv 값이 1을 넘어가면 여러 이미지가 출력되므로,
	// uv 값이 1을 넘어갈 때 어떻게 처리할 것인가.
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;

	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	
	//LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};

	blendDesc.RenderTarget[0].BlendEnable = true;

	// Src : 출력할 색상, Dest : 출력할 뒷배경 색상
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // Inverse Alpha = 1 - ALPHA

	// 위의 처리된 색상들을 어떻게 할 것인가.
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &blendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}
