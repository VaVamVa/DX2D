# N���� �����
<br>


1. Strip : n���� ������ ��ӵ� ������ ���� �մ� ��
    - ���� ������ ���� �ð������ �ո��� �ǹ��ϸ�, �ո鸸 ���.
    - ������ ���� �ʰ� ������, �޸�(��µ��� �ʴ� ��)�� ȭ���� �ٶ󺸰� ��.
        - ���� : �ð���� -> �ݽð� ���� �ݺ�

2. Line : n ���� ������ �մ� ��
    - �� ���� ������ ���� ¦�� �̷�� �������Ƿ�, �� ������ ������ �Է� �ؾ� ��.

- Polygon : ���� �� ������� ���� ���� �ﰢ���� �̷�� �Ͽ� �� ���θ� ä�� ��


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
vertices.emplace_back(+0.5f, +0.5f, 1, 0, 0);  // ù��° strip�� �ð� ��������
vertices.emplace_back(+0.5f, -0.5f, 1, 1, 1);  // �ι�° strip ���� �ð� �ݴ��.
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

// ���� ���� ������ ���� ����(Texture) ����
D3D11_BUFFER_DESC bufferDesc = {};
bufferDesc.Usage = D3D11_USAGE_DEFAULT;
bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

D3D11_SUBRESOURCE_DATA initData = {};
initData.pSysMem = vertices.data();  // ù �ּ�

device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);

```