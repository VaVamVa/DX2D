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

- [content_diff]()
    - project

#### 과제
- [???](https://github.com/VaVamVa/DX2D)
