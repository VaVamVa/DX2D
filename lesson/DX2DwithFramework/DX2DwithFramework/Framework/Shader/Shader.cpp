#include "Framework.h"
#include "Shader.h"

std::unordered_map<std::wstring, Shader*> Shader::shaders;
std::unordered_map<std::wstring, Shader*>::iterator Shader::iterator;

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::AddVS(std::wstring file)
{
    iterator = shaders.find(file);
    if (iterator != shaders.end())
        return (VertexShader*)iterator->second;

    std::wstring path = L"Shaders/" + file;
    VertexShader* newVertexShader = new VertexShader(path);
    shaders.insert({ file, newVertexShader });
    return newVertexShader;
}

PixelShader* Shader::AddPS(std::wstring file)
{
    iterator = shaders.find(file);
    if (iterator != shaders.end())
        return (PixelShader*)iterator->second;

    std::wstring path = L"Shaders/" + file;
    PixelShader* newPixelShader = new PixelShader(path);
    shaders.insert({ file, newPixelShader });
    return newPixelShader;
}

void Shader::Delete()
{
    for (iterator = shaders.begin(); iterator != shaders.end(); iterator++)
        delete iterator->second;
    shaders.clear();

}
