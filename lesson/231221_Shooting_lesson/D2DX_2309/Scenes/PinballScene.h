#pragma once

class PinballScene : public Scene
{
public:
	PinballScene();
	~PinballScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	class Flipper* left;
	class Flipper* right;
};