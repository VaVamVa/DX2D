#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
    : srv(srv), image(move(image))
{
}

Texture::~Texture()
{
    srv->Release();
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    textures[file] = new Texture(srv, image);

    return textures[file];
}
