## `imgui` library 적용법

1. 솔루션 우클릭->새 프로젝트-> "정적 라이브러리" 추가, 원래 있던 소스, 헤더파일 삭제
2. `imgui` 최신버전 다운로드 후 아래의 파일들 솔루션에 복사 & 붙여넣기, 프로젝트에 포함
    - `imgui-version/imgui-version` <br>
    ![ImGuiFiles](https://github.com/VaVamVa/DX2D/tree/main/DocuImages/ImGuiFiles.JPG)
    - `imgui-version/imgui-version/backends` <br>
    ![ImGuiBackendsFiles](https://github.com/VaVamVa/DX2D/tree/main/DocuImages/ImGuiBackendsFiles.JPG)
3. `ImGui` 솔루션에서 미리 컴파일된 헤더 사용하지 않음 한 후 빌드
4. `pjt/x64/Debug` 생성된 `본인이 만든 정적 라이브러리 솔루션 이름.lib`(`ImGui`) 파일을 본인 프로젝트의 `Libraries`에 붙여넣기
5. `pjt/Libraries`에 `ImGui` 폴더 생성 후, 정적 라이브러리 솔루션에 존재하는 모든 Header 파일 복사 & 붙여넣기, 프로젝트에 포함
    - (+) 유형별로 정리하면 헤더파일만 모을 수 있음.
6. 정적 라이브러리 (생성용) 솔루션 제거(&삭제)
7. `Framework.h` 에서 필요한 헤더파일들 포함시키고, 그 구현부를 `4`의 정적 라이브러리와 연결
```
#include "Libraries/ImGui/" + (imgui.h, imgui_impl_dx11.h, imgui_impl_win32.h)
#pragma comment(lib, "Libraries/Lib/ImGui.lib")
```

8. `main.cpp` 에서 `WinProc` 함수 위에 정적 라이브러리의 전역변수 가져오기
```cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
```

9. `WinProc` 함수에서 `ImGui` 수행용 함수 호출
```cpp
if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
{
    return true;
}
```

10. `GameManager` 생성자에서 아래의 코드 입력
```cpp
ImGui::CreateContext();
ImGui::StyleColorsDark();

ImGui_ImplWin32_Init(hWnd);
ImGui_ImplDX11_Init(DEVICE, DC);
```

11. `GameManager` 소멸자에서 아래의 코드 입력
```cpp
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();

ImGui::DestroyContext();
```

12. `GameManager::Render()`에서 `scene Render` 이후, `scene PostRender` 이전에 아래의 코드 입력
```cpp
ImGui_ImplDX11_NewFrame();
ImGui_ImplWin32_NewFrame();
    
ImGui::NewFrame();
```

13. `GameManager::Render()`에서 `scene PostRender` 이후에 아래의 코드 입력
```cpp
ImGui::Render();
ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
```

14. `Transform::GUIRender()` 정의.
    - `Transform` 객체의 `Postion`, `Rotation`, `Scale` 등<br> 속성들의 value를 `ImGui` component를 통해 수정할 수 있게 해주는 것.
    - `Transform::tag` 속성이 같을 경우 한번에 수정되니,<br>서로 다른 객체는 각각 다른 tag를 할당해 주어야 함.
```cpp
if (ImGui::TreeNode((tag + "_Transform").c_str()))
{
    ImGui::Text(tag.c_str());

    ImGui::Checkbox("Active", &isActive);

    string temp = tag + "_Pos";
    ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);

    temp = tag + "_Rot";
    Float3 rot;
    rot.x = XMConvertToDegrees(localRotation.x);
    rot.y = XMConvertToDegrees(localRotation.y);
    rot.z = XMConvertToDegrees(localRotation.z);

    ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

    localRotation.x = XMConvertToRadians(rot.x);
    localRotation.y = XMConvertToRadians(rot.y);
    localRotation.z = XMConvertToRadians(rot.z);

    temp = tag + "_Scale";
    ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);

    // 231222 수업에 쓰일 속성
    temp = tag + "_Pivot";
    ImGui::DragFloat2(temp.c_str(), (float*)&pivot, 0.1f);

    //if (ImGui::Button("Save"))
    //    Save();
    //
    //ImGui::SameLine();
    //
    //if (ImGui::Button("Load"))
    //    Load();

    ImGui::TreePop();
}
```

- (+) FPS 를 ImGui 컴포넌트에 띄우는 법.
    - `GameManager::Render()` 에서 `scene PostRender` 직전에.
```cpp
string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
ImGui::Text(fps.c_str());
```

- 기능 : 디버깅, 에디터 등