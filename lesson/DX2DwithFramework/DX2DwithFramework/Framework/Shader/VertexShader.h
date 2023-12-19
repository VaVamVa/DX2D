#pragma once

class VertexShader
{
private:
	VertexShader(ID3D11InputLayout* inputLayout, ID3D11VertexShader* shader);
	~VertexShader();

public:
	static VertexShader* Add(std::wstring file, D3D11_INPUT_ELEMENT_DESC layoutDesc[], int layoutSize);
	void Set();

	static void Destroy();

private:
	static std::unordered_map<std::wstring, VertexShader*> vertexShaders;

	ID3D11VertexShader* shader;
	ID3D11InputLayout* inputLayout;
};