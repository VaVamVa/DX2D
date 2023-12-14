#pragma once

class SRTScene : public Scene
{
public:
	SRTScene();
	~SRTScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Rect* rect;

	MatrixBuffer* worldBuffer;

	Matrix world;
	DirectX::XMFLOAT4X4 matWorld;

	Float2 pos = {}, scale = { 1.0f, 1.0f };
	float angle = 0.0f;
};