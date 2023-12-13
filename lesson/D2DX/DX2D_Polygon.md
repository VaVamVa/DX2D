# N각형 만들기
<br>


1. Strip : n개의 정점을 약속된 순서에 따라 잇는 선
    - 정점 순서에 따라 시계방향이 앞면을 의미하며, 앞면만 출력.
    - 순서에 맞지 않게 돌리면, 뒷면(출력되지 않는 면)이 화면을 바라보게 됨.
        - 순서 : 시계방향 -> 반시계 방향 반복

2. Line : n 개의 정점을 잇는 선
    - 한 쌍의 정점이 서로 짝을 이루어 묶어지므로, 두 정점씩 정보를 입력 해야 함.

- Polygon : 위의 두 방법으로 이은 선이 삼각형을 이루게 하여 그 내부를 채운 면


```cpp

/* tri_list to rect
vertices.emplace_back(+0.5f, +0.5f);
vertices.emplace_back(+0.5f, -0.5f);
vertices.emplace_back(-0.5f, -0.5f);

vertices.emplace_back(-0.5f, -0.5f);
vertices.emplace_back(-0.5f, +0.5f);
vertices.emplace_back(+0.5f, +0.5f);
*/

/* tri_strip to rect
vertices.emplace_back(+0.5f, +0.5f, 1, 0, 0);  // 첫번째 strip은 시계 방향으로
vertices.emplace_back(+0.5f, -0.5f, 1, 1, 1);  // 두번째 strip 부터 시계 반대로.
vertices.emplace_back(-0.5f, +0.5f, 0, 0, 1);
vertices.emplace_back(-0.5f, -0.5f, 0, 1, 0);
*/

/* tri_strip to penta
vertices.emplace_back(0.0f, 0.5f, 0, 1, 0);
vertices.emplace_back(0.5f, 0.0f, 0, 1, 0);
vertices.emplace_back(-0.5f, 0.0f, 0, 1, 0);
vertices.emplace_back(0.25f, -0.5f, 0, 1, 0);
vertices.emplace_back(-0.25f, -0.5f, 0, 1, 0);
*/

// Polygon
if (vertexNumber % 2)
{
    FOR(i, 1, vertexNumber + 1)
    {
        vertices.emplace_back(0, 0, 1, 1, 1);
        vertices.emplace_back(radius * sin(aVertexRadian * i), radius * cos(aVertexRadian * i), 1, 0, 0);
        vertices.emplace_back(radius * sin(aVertexRadian * (i + 1)), radius * cos(aVertexRadian * (i + 1)), 0, 0, 1);
    }
}
else
{
    FOR(i, 1, vertexNumber + 1)
    {
        vertices.emplace_back(0, 0, 1, 1, 1);
        vertices.emplace_back(radius * cos(aVertexRadian * i), radius * sin(aVertexRadian * i), 1, 0, 0);
        vertices.emplace_back(radius * cos(aVertexRadian * (i + 1)), radius * sin(aVertexRadian * (i + 1)), 0, 0, 1);
    }
}

// 위의 도형 정보를 담은 버퍼(Texture) 생성
D3D11_BUFFER_DESC bufferDesc = {};
bufferDesc.Usage = D3D11_USAGE_DEFAULT;
bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

D3D11_SUBRESOURCE_DATA initData = {};
initData.pSysMem = vertices.data();  // 첫 주소

device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);

```