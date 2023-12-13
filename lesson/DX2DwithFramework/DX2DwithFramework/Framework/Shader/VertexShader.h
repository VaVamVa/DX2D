#pragma once

class VertexShader
{
public:
	VertexShader(std::wstring file);
	~VertexShader();

	void Set();

private:
	ID3D11VertexShader* shader;
	ID3D11InputLayout* inputLayout;
};