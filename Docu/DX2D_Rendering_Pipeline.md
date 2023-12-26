# 물방울책 5장. 렌더링 파이프라인
<br>

p.160

## 1~3 모형과 색상의 표현 
p. 162
<br>

### 1. 3차원 형상


<br>

### 2. 모형의 표현


<br>

### 3. 색상 연산


<br>

## Rendering PipeLine
p.170
<br>

### 1. 수업 내용

GPU가 화면에 출력하는 과정
1. Input Assembler(IA) : CPU에 있는 정보를 가져오는 단계
2. Vertex Shader : 정점 쉐이더
(3.) Hull Shader, tS, Depth Stencil, Geometry Shader
4. Rasterizer State : NDC 좌표를 출력하기 위해 viewPort 변환을 해주는 과정.
    - 또한 폴리곤(STRIP)에서 color를 선형보간으로 채워준다.
5. Pixel Shader
6. OM : Output Merge
<br>

Shader : GPU 언어. - 우리가 짜야하는 스크립트
- hlsl(hi-level shader language)
- 확장-확장 관리-HLSL Tool for Visual Studio 검색/설치
    - 만약 자동으로 작업관리자 Manage bar 보일경우 해당 버튼 클릭 후 추가설치 X
- 프로젝트 속성-HLSL 컴파일러-진입점 이름 : VS, 셰이더 모델 ShaderModel 5.0 (DX11 용)
- 추가-새 항목-Visual C++-HLSL-헤더파일
    - [예시](https://github.com/VaVamVa/DX2D/blob/main/lesson/D2DX/D2DX/Shaders/Tutorial.hlsl)
<br>

### 2. 책 내용 주제

![pipeline](https://github.com/VaVamVa/DX2D/blob/main/DocuImages/Rendering_Pipeline_Levels.jpg)

1. (5.5) Input Assemler : 메모리에서 기하 자료를 읽어서 기하학적 기본도형 조립
2. (5.6) Vertex Shader : (개발자 이용) 정점 하나를 받아서 정점 하나를 <b>출력</b>하는 함수들의 수행
3. (5.7) Tessellation : 한 mesh의 삼각형들을 더 잘게 쪼개서 더 세밀한 삼각형 생성
4. (5.8)Geometry Shader : (생략 가능) 하나의 온전한 기본도형을 입력 받아 임의로 변형
	- Stream Output : RAM에 일시 저장
5. (5.9) Clipping : 절두체를 벗어난 기하구조 폐기
6. (5.10) Rasterization Stage : 투영된 3차원 삼각형으로부터 픽셀 색상 계산
    - 뷰포트 변환, 후면 선별, 정점 특성 보간 등
7. (5.11) Pixel Shader : (개발자 이용) 주어진 정점 특성을 입력받아 각각의 픽셀 단편에 색상을 출력
8. (5.12) Output Merger : 깊이 판정이나 스텐실 판정 후 픽셀 단편을 후면버퍼에 기록
<br>

### 3. 요약
p.203~4

(기입 필요)
#### 1.

<br>
