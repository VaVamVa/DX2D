# DX2D TIL
<br>

### 1. 231211
DirectX 초기화 - device, device context 에 대한 DESC 입력 및 인터페이스 할당(참조)/ rtv, swap chain 선언
- [content_diff](https://github.com/VaVamVa/DX2D/commit/24ab2b2bef0dba8af42210bfbd6ef1dfd588eaa5)
    - D2DX.cpp, framework.h
#### 과제
- [DirectX 기본 개념](lesson/D2DX/DX2D_Concepts.md)
- [DirectX 초기화](lesson/D2DX/DX2D_Init.md)

<br>

### 2. 231212
Shader 스크립트 만들기 (Vertex Shader, Pixel Shader) with Rendering Pipeline
- [content_diff](https://github.com/VaVamVa/DX2D/commit/afc45d158c08266274633960fbd010fb9cf9804a)
    - D2DX.cpp
    - Shader Script의 컴파일을 위한 HLSL 컴파일 진입점과 Shader Model version을 정해줘야 함.
        - 수업 pjt의 경우, VS가 첫 함수이므로 VS를 진입점으로 잡고, Shader Model은 DX11에서 version 5.0으로 지정.
- [포프의_쉐이더_입문강좌_1](https://blog.popekim.com/ko/2011/11/29/intro-to-shader-01-what-is-shader-part-1.html)
#### 과제
- [n각형 그리기](lesson/D2DX/DX2D_Polygon.md)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/d24c9f0f0a10abf64334369e41181b60a2b805aa)

<br>

### 3. 231213
`1`, `2` 내용을 기반으로 Framework 구축하기
- [content_diff](https://github.com/VaVamVa/DX2D/commit/26557ec506220713760249e319f45f8f3f570d5c)
    - project 전체적으로.
- 물방울책 4장~6장
```
Framework/
    - Render [Device, DC, swap chain, rtv]
    - Shader [VS, PS] - 6장 p.211
    - Buffer [Vertex(with Layout), Index, Constant(in Global)]

Manager/ GameManager : set viewport, Alloc Scene

Scenes/ TutorialScene : Alloc&Set Shaders, Alloc&Set Buffers, (indexed line type)Draw

Shaders/ Tutorial.hlsl : structs for Vertex & Pixel , 3 const buffers for wvp transpose
```
    

#### 과제
- [DirectX 렌더링 파이프라인](lesson/DX2DwithFramework/DX2D_Rendering_Pipeline.md)

<br>

### 4. 231214
객체 SRT 구현
- [content_diff](https://github.com/VaVamVa/DX2D/commit/d9b2fc7f7b0142588afba8062d258f70859dbf70)
    - project
```
Framework/
    - Environment : viewport, projection buffer

Scenes/ SRT scene : Alloc&Set object, Alloc&Set world buffer,
    matWorld : for matrix calculate, wolrd matrix for setting world buffer,
    object attributes

Objects for init vertices to vertex buffer&shader (with pixel buffer&shader)
```

1. viewport 생성&설정 및 view buffer, projection buffer 생성&설정을 Environment 객체로 뺌.
    - Framework/Environment
2. SRT scene 를 새로 만듦. world buffer를 이 객체에 선언&할당
    - Scale, Rotation, Translation
3. 별도의 Object 객체로 vertices를 뺌
    - 추후 world buffer도 빼서 객체의 움직임 (SRT) 구현함.

#### 과제
- [Plane](https://github.com/VaVamVa/DX2D/lesson/DX2DwithFramework/DX2DwithFramework/Scenes/PlaneScene.h)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/f27113ed0ee3f6be64364c921f56baa970dc3b4e)
- [Plane_codu](https://github.com/VaVamVa/DX2D/lesson/DX2DwithFramework/DX2D_SRTmatrix.md)

<br>

### 5. 231215
(Rect->Quad 이름변경)
1. Quad 객체 상위에 Transform 객체를 둚으로서, SRT 행위들을 상위 객체에서 상속,<br> 해당 world 행렬을 이 객체에서 다룸.
2. DirectX Tex 외부 리소스 다운로드

```cpp
--DirectX tex 정적 library 설치 및 적용--
google-DirectX tex 검색- Microsoft github.
Release 프로젝트 중 제일 최신 버전에서 Assets-Source code(zip) 설치.

DirectXTex_Desktop_2022_Win10 solution pjt 열고 빌드하기.

\DirectXTex-oct2023\DirectXTex-oct2023\DirectXTex
에서 DirectXTex.h, DirectXTex.ini 파일 복사하여
내 프로젝트 Libraries 하위에 DirectXTex 폴더 생성 후 붙여넣기.

\DirectXTex-oct2023\DirectXTex-oct2023\DirectXTex\Bin\Desktop_2022_Win10\x64\Debug
에서 lib 파일을 복사하여 내 프로젝트 Libraries/Lib/ 폴더 하위에 붙여넣기

#include "Libraries/DirectXTex/DirectXTex.h"
#pragma comment(lib, "Libraries/lib/DirectXTex.lib")
추가하기
```

3. 외부 resource를 폴리곤으로 잘라 붙이기 위한 새로운 vertex & pixel hlsl 파일 생성
    - float4 color -> float2 uv
    - layout 변경 해줘야함
    - pixel shader가 따로 파일로 만들었기 때문에 이 파일의 진입점 재설정.
4. resource 이용을 위한 Texture 객체 생성 (`srv`, 그대로는 참조 불가능한 `image`)
5. Environment 객체에서 sampler와 blend 인터페이스 이용 추가.

- [content_diff](https://github.com/VaVamVa/DX2D/commit/88020006a3a965ff8e90c44dedd138075e37d5ab)

#### 과제
- [Plane](https://github.com/VaVamVa/DX2D/tree/main/lesson/DX2DwithFramework/DX2DwithFramework)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/f79c48b92800e9edd16971c85ab86e2e54715c6f)
1. Vertex Shader와 Pixel Shader를 각각 한 종류(?_Shader 방식? hlsl 파일?) 당 1개 씩 생성해 주었음
2. api 때 했던 로직과 유사하게 객체들의 구조를 짰음.
- 빠르게 구현하기 위해 tsv 파일을 썼으나, String parser를 이용하여 csv 파일을 쓸 수 있게 수정 필요.

<br>

### 5. 231220
1. Shader에 대한 static container를 가지는 하나의 super class를 두어 중복 생성 관리 (`4.231215`는 각 Shader 객체에서 관리했음.)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/8fe456b561b8cef8622fd8e2573ad35178fe1b80)
2. obj를 한 묶음으로 관리하게 함.
    - 변경된 점이 많아 수업의 프로젝트를 그대로 가져옴.
3. background 생성, depth에 따라 차등 Render
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/3841aefdc76516a76f54c063e80bc78a04b7af3b)