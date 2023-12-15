#pragma once

class Environment : public Singleton<Environment>
{
private:
	friend Singleton;
	Environment();
	~Environment();

private:
	void SetViewport();
	void SetProjection();

	void CreateSamplerState();
	void CreateBlendState();

private:
	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* blendState;
};