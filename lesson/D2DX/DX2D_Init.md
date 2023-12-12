# 물방울책 4장. Direct3D의 초기화
<br>

p.115

## 2. Direct3D의 초기화
<br>

### 0. 개요

[기준_code](./D2DX/D2DX.cpp)

1. `D3D11CreateDevice` 함수를 이용하여 장치(`ID3D11Device`) 인터페이스와 장치 문맥(`ID3D11DeviceContext`) 인터페이스 생성.
2. ~~`ID3D11Device::CheckMultisampleQualityLevels` 메서드를 이용하여 4XMSAA 품질 수준 지원 여부 점검~~
3. 생성할 교환 사슬의 특성을 서술하는 `DXGI_SWAP_CHAIN_DESC` 구조체의 멤버 할당.
4. ~~장치를 생성하는데 사용했던 `IDXGIFactory` 인터페이스를 질의 해서~~ `IDXGISwapChain` 인스턴스 생성.
5. 교환 사슬의 후면 버퍼에 대한 렌더 대상 뷰(`ID3D11RenderTargetView`) 생성.
6. 깊이-스텐실 버퍼와 그에 연결되는 깊이-스텐실 뷰 생성.
7. 렌더 대상 뷰와 깊이-스텐실 뷰를 Direct3D가 사용할 수 있도록 렌더링 파이프라인의 출력 병합기 단계에 묶기(binding).
8. 뷰포트 설정.

<br>

### 1.


<br>

### 2.


<br>

### 3.


<br>

### 4.


<br>

### 5.


<br>

### 6.


<br>

### 7.


<br>

### 8.


<br>
