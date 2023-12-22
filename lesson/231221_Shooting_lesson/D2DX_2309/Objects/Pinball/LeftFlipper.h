#pragma once

class LeftFlipper : public Flipper
{
public:
	LeftFlipper();
	~LeftFlipper();

private:
	bool Rotate() override;
};