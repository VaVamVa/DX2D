#pragma once

class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, DirectX::ScratchImage& image);
	~Texture();

public:
	static Texture* Add(std::wstring file);

public:
	void PSSet(UINT slot = 0);

	Vector2D GetSize()
	{
		return Vector2D(image.GetMetadata().width, image.GetMetadata().height);
	}
	
private:
	DirectX::ScratchImage image;
	ID3D11ShaderResourceView* srv;

	static std::unordered_map<std::wstring, Texture*> textures;
};