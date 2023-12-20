#pragma once

class Shader
{
protected:
	Shader() = default;
	virtual ~Shader();

public:
	static class VertexShader* AddVS(std::wstring file);
	static class PixelShader* AddPS(std::wstring file);
	static void Delete();

	virtual void Set() = 0;

protected:
	// https://learn.microsoft.com/ko-kr/windows/win32/api/d3dcommon/nn-d3dcommon-id3d10blob
	ID3DBlob* blob;  // buffer -> shader 데이터 변환용 (데이터 주소 및 크기 정보용 인터페이스)

	static std::unordered_map<std::wstring, Shader*> shaders;
	static std::unordered_map<std::wstring, Shader*>::iterator iterator;
};