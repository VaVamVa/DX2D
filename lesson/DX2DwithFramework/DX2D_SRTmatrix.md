# Plane & Bullets

- [pjt](./DX2DwithFramework)

### World Buffer


### 행렬 곱을 이용한 Wolrd Buffer 수정
- DirectX의 `Matrix` type은 float 4 * 4 행렬이다.
    - 이를 이용해 위의 world buffer에 값을 전달하여 객체의 상태를 수정할 수 있다.
    - (전치행렬로 만들어 주어 연산하는 것이 더 빠르기에 전치행렬로 바꿔서 world buffer에 전달함.)
<br>

```
기본 형태.
m11 m12 m13 m14
m21 m22 m23 m24
m31 m32 m33 m34
m41 m42 m43 m44

객체가 가지고 있는 상태 행렬 (vertex status).
(w, h, 0, 1) _x, y, z, w(==for calculate(?))
위의 1*4 행렬이 vertices 갯수만큼 존재.
```

<br>

1. `DirectX::XMFLOAT4X4` 을 이용하는 방법
```
DirectX::XMFLOAT4X4 matWorld = MatrixBuffer;
matWorld 초기상태.
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1


```

    1. scale

2. `DirectX::XMMatrix_Fuctions` 를 이용하는 방법.
    - `1`의 행렬 연산들과 같은 과정을 자동으로 연산해주는 함수들이다.

### SRT matirx
