#pragma once

class RightFlipper : public Flipper
{
public:
	RightFlipper();
	~RightFlipper();

private:
	bool Rotate() override;
};