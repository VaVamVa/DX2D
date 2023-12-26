# DX2D TIL
<br>

## 우선 해야할 일.
- 물방울책 5장~8장 정리
- 날짜별 파일 생성 & 정리하기.
    - 각 md파일 한 폴더에 몰아두고, 경로 재지정
    - 날짜 & 간단한 설명만 대문에 남기기.

### 1. 231211
DirectX 초기화 - device, device context 에 대한 DESC 입력 및 인터페이스 할당(참조)/ rtv, swap chain 선언
- [content_diff](https://github.com/VaVamVa/DX2D/commit/24ab2b2bef0dba8af42210bfbd6ef1dfd588eaa5)
    - D2DX.cpp, framework.h
#### 과제
- [DirectX 기본 개념](https://github.com/VaVamVa/DX2D/blob/main/Docu/DX2D_Concepts.md)
- [DirectX 초기화](https://github.com/VaVamVa/DX2D/blob/main/Docu/DX2D_Init.md)

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
- [DirectX 렌더링 파이프라인](https://github.com/VaVamVa/DX2D/blob/main/Docu/DX2D_Rendering_Pipeline.md)

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

2. [DirectX_Tex_적용법](https://github.com/VaVamVa/DX2D/blob/main/lesson/DX2DwithFramework/DirectX_Tex.md)


- [content_diff](https://github.com/VaVamVa/DX2D/commit/88020006a3a965ff8e90c44dedd138075e37d5ab)

#### 과제
- [Plane](https://github.com/VaVamVa/DX2D/tree/main/lesson/DX2DwithFramework/DX2DwithFramework)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/f79c48b92800e9edd16971c85ab86e2e54715c6f)
1. Vertex Shader와 Pixel Shader를 각각 한 종류(?_Shader 방식? hlsl 파일?) 당 1개 씩 생성해 주었음
2. api 때 했던 로직과 유사하게 객체들의 구조를 짰음.
- 빠르게 구현하기 위해 tsv 파일을 썼으나, String parser를 이용하여 csv 파일을 쓸 수 있게 수정 필요.

<br>

### 5. 231219
1. Shader에 대한 static container를 가지는 하나의 super class를 두어 중복 생성 관리 (`4.231215`는 각 Shader 객체에서 관리했음.)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/8fe456b561b8cef8622fd8e2573ad35178fe1b80)
2. [obj를 한 묶음으로 관리하게 함](https://github.com/VaVamVa/DX2D/blob/main/lesson/231219_Shooting_lesson/D2DX_2309/Objects/Basic/ObjectManager.h)
    - 변경된 점이 많아 수업의 프로젝트를 그대로 가져옴.
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/3841aefdc76516a76f54c063e80bc78a04b7af3b)
    - ObjectManager 에서 depth에 따라 차등 Render
        - container로서 `multimap` 이용. depth를 key로 두어 오름차순으로 후에 Render되도록 설계.
3. background 생성.

<br>
  
### 6. 231220

1. 원형 경기장 설정 및 원형 경기장 밖으로 못 빠져나가게 구현.
   - sliding vector를 구하려고 했으나, 구현에 어려움이 있어 차선책으로 `push land` 이용.
   ```cpp
     /*
    if (distance >= MAP_RADIUS)
    {
        // sliding vector
        velocity = velocity - normalVector * Dot(velocity, normalVector);

        Translate(normalVector * MAP_PUSH_SPEED * DELTA);
    }
    */
    if (distance >= MAP_RADIUS)
    {
        Vector2 normalVector = (CENTER - localPosition).GetNormalized();
        Translate(normalVector * MAP_PUSH_SPEED * DELTA);
    }
     ```
     - [reference](https://toymaker.tistory.com/entry/%EB%AF%B8%EB%81%84%EB%9F%AC%EC%A7%90-%EB%B2%A1%ED%84%B0-Sliding-Vector)

2. Collider 객체 생성, 해당 객체를 충돌이 가능한 객체에 참조.
3. Collider 가능한 범위 표현을 위해 Line Strip를 Shade 해주기 위해 새로운 `Shader` 생성.
    - [VertexPos](https://github.com/VaVamVa/DX2D/blob/main/lesson/231219_Shooting_lesson/D2DX_2309/Shaders/VertexPos.hlsl), [PixelPos](https://github.com/VaVamVa/DX2D/blob/main/lesson/231219_Shooting_lesson/D2DX_2309/Shaders/PixelPos.hlsl) Shader 생성.
    - 이때 `PixelPos Shader`에 Color를 전달해 줄 ConstBuffer를 상속받는 Color Buffer 생성.
    - `Collider`객체에서 Line Strip에 대한 On/Off 설정 가능하게 함.
        -  `Collder::isDraw`속성,<br> `Collider::TotalUpdate()`, `Collider::TotalRender()`
        - [Collider.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Collider/Collider.cpp)
4. `3`을 기반으로 plane, enemy, bullet 객체 collider 참조하여 collision 구현.(과제)
    - [content_diff](https://github.com/VaVamVa/DX2D/commit/49f5dcf1a26a5019a688d09d0fbb70a3f9c3412a)
    - A 객체가 참조하는 collider는 A객체를 `Transform::parent`로 가짐.
    - 이제부터 `active` 판단을 직접 속성으로 하는 것이 아닌, 무조건 함수 `Transform::IsActive()`로 판단하여 부모의 active 상태를 따라갈 수 있게 함.
        - [Trasnform.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Math/Transform.cpp)

- [content_diff](https://github.com/VaVamVa/DX2D/commit/845c5b034b6724783dc046b8bbbf4b4d694c7d6a)

<br>
  
### 7. 231221
<br>

#### ShootingScene

1. 새로운 [PxielBGLightShader](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Shaders/PixelBGLight.hlsl) 생성.
    - Texture와 색상을 곱하여 Shade 함.
    - shader를 angle에 따라 rotate 해줌 (회전 행렬)

2. `bg2` Texture를 따로 생성해준 후, 이를 `1`의 새로운 PixelShader에 적용. `PSSet(1)`

#### ImGui 적용법

1. [ImGui](https://github.com/VaVamVa/DX2D/tree/main/Docu/DirectX_ImGui.md)

<br>

#### CollisionScene

1. `imgui` 적용.

2. `Vector2`와 행렬을 계산해 주기 위한 연산자 오버로딩 구현
    - [Vector2](https://github.com/VaVamVa/DX2D/blob/main/lesson/231219_Shooting_lesson/D2DX_2309/Framework/Math/Vector2.h)

3. 회전한 네모 객체 `Point Collision` 구현.
    - 회전한 상태는 world buffer에 의한것.
    - 이에 역행렬을 구해 곱해주면 (0,0) 위치 회전하기 전 사각형 객체로 되돌릴 수 있음
    - 똑같이 `Point`도 이 역행렬을 곱해주고, 판단.

<br>

- [content_diff](https://github.com/VaVamVa/DX2D/commit/fcf2e6827baec335a7dfcafef90777ecd0b06462)

<br>
  
### 7. 231222
<br>

1. pivot rotate
    1. `Transform` 객체에 `pivot` 속성을 추가하여 회전 기준을 새로 정립.
    2. `Transform::UpdateWorld()`에서 `Matrix P`를 정의하고,<br>
    이에 대한 역행렬 `invP`를 정의.
    3. `world buffer`에 전달하는 방식을 아래와 같이 변경<br>
    ```cpp
    // world = S * R * T;
    // ->
    world = invP * S * R * T * P;
    ```
    - 이제부터 pivot 좌표를 기준으로 회전 가능.
    - [Transform.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Math/Transform.cpp)

2. obb collision
    - SAT(Separating Axis Theorem, 분리축 이론)을 이용한<br>OBB(Oriented Bounding Box, 방향을 가지는 경계 상자)
        - AABB 는 모든 경계상자를 공통된 축을 가지고 판단하고,<br>OBB는 경계 상자에 기반한 축을 가지고 판단한다.
    - 경계상자는 직사각형으로 간주하고 판단. (축이 두개)
        - `Transform::UpdateWorld()`에서 `Transform::rightVector`, `Transform::upVector` 경계상자에 대한 축 속성을 갱신.
    - [Transform.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Math/Transform.cpp)
    - `RectCollider::IsSparate()` 로 사각형 끼리의 충돌 판단.
        - [RectCollider.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Collider/RectCollider.cpp)

3. raterizerState setting
    - `polygon` 은 시계 반대방향으로 객체를 생성할 경우 뒷 면임을 뜻함.
        - "뒷 면"은 빛이 반사되어도 우리에게 보이지 않음.
    - 위의 상황에서 뒷 면도 앞 면과 같이 화면에 투영해 주는 설정.
    - `Environment::CreateRasterizerState()`
        - [Environment.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231221_Shooting_lesson/D2DX_2309/Framework/Environment/Environment.cpp)

- [content_diff](https://github.com/VaVamVa/DX2D/commit/0003fe3692b259f71ac256e62ede361bb9013f1e)

<br>
  
### 7. 231226
<br>

#### binary wirter/reader 
`0b Type write&read`

1. `void*`를 이용하여 자료형에 대응되는 자료들 저장 및 읽기.
    - 순서 중요.

2. `void*` data, LPC

3. `.srt` 형식으로 저장

#### Object Editing

1. `Transform::GUIRender`를 이용해 각 객체와 `collider`를 GUI Editor로 표현한다.
2. 각 Objects와 Collider를 손으로 edit 한 뒤(hard coding) `Save`
3. 객체들의 생성자에 `Transform::Load()`를 이용해 이전의 상태 복원

- [Pinball/Objects](https://github.com/VaVamVa/DX2D/tree/main/lesson/231222_RectCollider/D2DX_2309/Objects/Pinball)

#### 선형보간을 이용해 `Flipper::Control 구현`

- [GameMath.h](https://github.com/VaVamVa/DX2D/blob/main/lesson/231222_RectCollider/D2DX_2309/Framework/Math/GameMath.h)
- [Flipper.cpp](https://github.com/VaVamVa/DX2D/blob/main/lesson/231222_RectCollider/D2DX_2309/Objects/Pinball/Flipper.cpp)

<br>

- [content_diff]()

#### 과제
- Pinball