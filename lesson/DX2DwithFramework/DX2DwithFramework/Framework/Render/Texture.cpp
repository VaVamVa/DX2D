#include "Framework.h"

std::unordered_map<std::wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, DirectX::ScratchImage& image)
	:srv(srv), image(std::move(image))
{
}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Add(std::wstring file)
{
	if (textures.count(file) > 0)
		return textures[file];

	DirectX::ScratchImage image;
	DirectX::LoadFromWICFile(file.c_str(),
		DirectX::WIC_FLAGS_NONE, nullptr, image);

	ID3D11ShaderResourceView* srv;
	DirectX::CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
		image.GetMetadata(), &srv);

	textures[file] = new Texture(srv, image);

	return textures[file];
}

void Texture::PSSet(UINT slot)
{
	DC->PSSetShaderResources(0, 1, &srv);
}
