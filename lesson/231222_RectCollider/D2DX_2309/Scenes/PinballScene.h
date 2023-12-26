#pragma once

class PinballScene : public Scene
{
public:
	PinballScene();
	~PinballScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
};