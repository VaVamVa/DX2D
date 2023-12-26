# Plane & Bullets

- [pjt](./DX2DwithFramework)

<br>

## World Buffer
- projection buffer : viewport 창을 하나의 정좌표계로 설정해주는 버퍼.
- 위의 projection buffer가 Vertex buffer 곱해지기 전, vertex의 상태를 바꿔주는 버퍼.
- view buffer : world buffer의 부모라 생각하자.


<br><br>

## 행렬 곱을 이용한 Wolrd Buffer 수정
DirectX의 `Matrix` type은 float 4 * 4 행렬이다.
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
(w, h, 0, 1) => x, y, z, w(==for calculate(?))
위의 1*4 행렬이 vertices 갯수만큼 존재.
```

<br>

### 1. `DirectX::XMFLOAT4X4` 을 이용하는 방법
```
DirectX::XMFLOAT4X4 matWorld (MatrixBuffer);
matWorld 초기상태.
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1

여기서 행렬의 특정 성분을 조정한 후,
vertex matrix (1*4)와 행렬곱을 해주면 특정 상태의 vertex matrix 결과가 나온다.
```

1. 
```
m11, m22가 각각 너비와 높이가 변하게끔 행렬곱 결과가 나온다.
```

2. Rotation
```
x, y에 대해
cos sin
-sin cos
의 곱을 하게 되면 행렬 회전이 되고,
2D에서는 z 축 회전으로 xy 회전 가능하기에
m11 m12
m21 m22
로 조절 가능하다.
```

3. Position (translation)
```
m41, m42의 값을 조정해주면 각각 x, y 에 더해지게끔 행렬곱 결과가 나온다.
```

### 2. `DirectX::XMMatrix_Fuctions` 를 이용하는 방법.
- `1`의 행렬 연산들과 같은 과정을 자동으로 연산해주는 함수들이다.

<br><br>

## SRT matirx

