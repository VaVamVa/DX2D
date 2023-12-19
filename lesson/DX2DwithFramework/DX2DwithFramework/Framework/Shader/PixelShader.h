#pragma once

class PixelShader
{
private:
	PixelShader(ID3D11PixelShader* shader);
	~PixelShader();

public:
	static PixelShader* Add(std::wstring file);
	void Set();

	static void Destroy();

private:
	static std::unordered_map<std::wstring, PixelShader*> pixelShaders;

	ID3D11PixelShader* shader;
};