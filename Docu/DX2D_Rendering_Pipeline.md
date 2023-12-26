# �����å 5��. ������ ����������
<br>

p.160

## 1~3 ������ ������ ǥ�� 
p. 162
<br>

### 1. 3���� ����


<br>

### 2. ������ ǥ��


<br>

### 3. ���� ����


<br>

## Rendering PipeLine
p.170
<br>

### 1. ���� ����

GPU�� ȭ�鿡 ����ϴ� ����
1. Input Assembler(IA) : CPU�� �ִ� ������ �������� �ܰ�
2. Vertex Shader : ���� ���̴�
(3.) Hull Shader, tS, Depth Stencil, Geometry Shader
4. Rasterizer State : NDC ��ǥ�� ����ϱ� ���� viewPort ��ȯ�� ���ִ� ����.
    - ���� �����￡�� color�� ������������ ä���ش�.
5. Pixel Shader
6. OM : Output Merge
<br>

Shader : GPU ���. - �츮�� ¥���ϴ� ��ũ��Ʈ
- hlsl(hi-level shader language)
- Ȯ��-Ȯ�� ����-HLSL Tool for Visual Studio �˻�/��ġ
    - ���� �ڵ����� �۾������� Manage bar ���ϰ�� �ش� ��ư Ŭ�� �� �߰���ġ X
- ������Ʈ �Ӽ�-HLSL �����Ϸ�-������ �̸� : VS, ���̴� �� ShaderModel 5.0 (DX11 ��)
- �߰�-�� �׸�-Visual C++-HLSL-�������
    - [����](https://github.com/VaVamVa/DX2D/blob/main/lesson/D2DX/D2DX/Shaders/Tutorial.hlsl)
<br>

### 2. å ���� ����

![pipeline](https://github.com/VaVamVa/DX2D/blob/main/DocuImages/Rendering_Pipeline_Levels.jpg)

1. (5.5) Input Assemler : �޸𸮿��� ���� �ڷḦ �о �������� �⺻���� ����
2. (5.6) Vertex Shader : (������ �̿�) ���� �ϳ��� �޾Ƽ� ���� �ϳ��� <b>���</b>�ϴ� �Լ����� ����
3. (5.7) Tessellation : �� mesh�� �ﰢ������ �� �߰� �ɰ��� �� ������ �ﰢ�� ����
4. (5.8) Geometry Shader : (���� ����) �ϳ��� ������ �⺻������ �Է� �޾� ���Ƿ� ����
	- Stream Output : RAM�� �Ͻ� ����
5. (5.9) Clipping : ����ü�� ��� ���ϱ��� ���
6. (5.10) Rasterization Stage : ������ 3���� �ﰢ�����κ��� �ȼ� ���� ���
    - ����Ʈ ��ȯ, �ĸ� ����, ���� Ư�� ���� ��
7. (5.11) Pixel Shader : (������ �̿�) �־��� ���� Ư���� �Է¹޾� ������ �ȼ� ������ ������ ���
8. (5.12) Output Merger : ���� �����̳� ���ٽ� ���� �� �ȼ� ������ �ĸ���ۿ� ���
<br>

### 3. ���
p.203~4

(���� �ʿ�)
#### 1.

<br>
