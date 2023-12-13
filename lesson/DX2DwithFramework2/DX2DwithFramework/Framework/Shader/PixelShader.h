#pragma once

class PixelShader
{
public:
	PixelShader(std::wstring file);
	~PixelShader();

	void Set();

private:
	ID3D11PixelShader* shader;
};