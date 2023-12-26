### 1. DirectX Tex 외부 리소스 다운로드

1. google-DirectX tex 검색- Microsoft github.
2. Release 프로젝트 중 제일 최신 버전에서 Assets-Source code(zip) 설치.
3. 프로젝트 솔루션 폴더 내에 `Libraries` 폴더 생성
4. `pjt/Libraries` 하위에 `DirectXTex`, `Lib` 폴더 생성
    - `DirectXTex` : 만들어진 외부 헤더 파일들을 저장할 폴더.
    - `Lib` : 외부 헤더 파일에 대한 정적 라이브러리 저장 장소.

### 2. DirectX tex 정적 library 설치 및 적용

1. `DirectXTex_Desktop_2022_Win10`의 `solution` 열고 "빌드하기".

2. `\DirectXTex-oct2023\DirectXTex-oct2023\DirectXTex`에서<br>
`DirectXTex.h`, `DirectXTex.ini` 파일 복사하여<br>
`pjt/Libraries/DirectXTex`에 붙여넣기.

3. `\DirectXTex-oct2023\DirectXTex-oct2023\DirectXTex\Bin\Desktop_2022_Win10\x64\Debug` 에서<br>
lib 파일을 복사하여 내 프로젝트 `Libraries/Lib/`에 붙여넣기

4. 아래의 코드를 `Framework.h`에 추가하기
```cpp
#include "Libraries/DirectXTex/DirectXTex.h"
#pragma comment(lib, "Libraries/lib/DirectXTex.lib")
```

### 3. DirectX Tex를 이용한 Texture UV load

- [uv_추가자료](https://blog.naver.com/hblee4119/222150877699)<br>
![UV_coord](https://github.com/VaVamVa/DX2D/blob/main/DocuImages/UV_coord.PNG)

1. 외부 resource를 폴리곤으로 잘라 붙이기 위한 새로운 vertex & pixel hlsl 파일 생성
    - float4 color -> float2 uv
    - layout 변경 해줘야함
    - pixel shader가 따로 파일로 만들었기 때문에 이 파일의 진입점 재설정.
    - [VertexUVShader.hlsl](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Shaders/VertexUV.hlsl)
    - [PixelUVShader.hlsl](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Shaders/PixelUV.hlsl)

2. resource 이용을 위한 Texture 객체 생성 (`srv`, 그대로는 참조 불가능한 `ScratchImage`)
    - `srv` : Shader Resource View. Texture 정보를 VRAM 으로 전달.
    - `ScratchImage` : DirectX Tex의 객체로서, Texture image의 여러 정보를 담고 있다.
    - [Texture.h](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Render/Texture.h)

3. Environment 객체에서 sampler와 blend 인터페이스 이용 추가.
```cpp
void Environment::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    //LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

    DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    DEVICE->CreateBlendState(&blendDesc, &blendState);

    float blendFactor[4] = {};
    DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

```
- [Environment.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Environment/Environment.cpp)

- UV의 값에 따라 Texture Rendering 효과를 줄 수 있는데,<br>
이 때 어떻게 Rendring 할 것인가를 위의 두 `Desc`객체를 통해 전달 가능
    - 추가 공부 필요