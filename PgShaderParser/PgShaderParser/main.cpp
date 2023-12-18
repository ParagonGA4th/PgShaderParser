#include "PgApp.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_gdi.h"

#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <memory>
#include <dinput.h>
#include <tchar.h>

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char**)
{
	//윈도우 만들기 (WinAPI)
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("PgShaderParser"), NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("PgShaderParser"), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	//Window 띄우기.
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	//Shader Parser 클래스.
	std::unique_ptr<Pg::PgApp> tApp = std::make_unique<Pg::PgApp>();
	tApp->Initialize();

	// IMGUI Context 체크.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//어두운 스타일.
	ImGui::StyleColorsDark();

	//Win32/GDI Fork 버전 Init.
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplGDI_Init();

	//Pretendard Font Loading.
	ImFont* smallFont = io.Fonts->AddFontFromFileTTF("../Fonts/Pretendard-Medium.ttf", 18.0f, NULL,
		io.Fonts->GetGlyphRangesKorean());
	IM_ASSERT(smallFont != NULL);

	ImFont* bigFont = io.Fonts->AddFontFromFileTTF("../Fonts/Pretendard-Medium.ttf", 25.0f, NULL,
		io.Fonts->GetGlyphRangesKorean());
	IM_ASSERT(bigFont != NULL);

	//Settings + Clear Color.
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(39.f, 37.f, 76.f, 1.00f);

	//io : body만 touch해서 움직이는 설정 해제.
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	//메인 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}
		// IMGUI 프레임 시작.
		ImGui_ImplGDI_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//Tool Controls
		{
			ImGui::SetNextWindowSize(ImVec2(480.f, 400.f));
			ImGui::Begin("Tool Controls");                          // Create a window called "Hello, world!" and append into it.
			ImGui::PushFont(smallFont);
			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//Render Buttons
			ImGui::PushFont(bigFont);
			if (ImGui::Button("Open Material", ImVec2(150.f, 75.f)))
			{
				tApp->OpenFileButtonPressed();
			}
			ImGui::SameLine();
			if (ImGui::Button("Save Material", ImVec2(150.f, 75.f)))
			{
				tApp->SaveFileButtonPressed();
			}
			ImGui::SameLine();
			if (ImGui::Button("Edit Material", ImVec2(150.f, 75.f)))
			{
				tApp->EditFileButtonPressed();
			}
			ImGui::PopFont();
			//ImGui::Text("counter = %d", counter);
			//
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			ImGui::PopFont();
			ImGui::End();
		}

		// 3. Show another simple window.
		//if (ImGui::BeginTable("table1", 3))
		//{
		//	ImGui::SetNextWindowSize(ImVec2(480.f, 400.f));
		//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		//	ImGui::Text("Hello from another window!");
		//	if (ImGui::Button("Close Me"))
		//		show_another_window = false;
		//	ImGui::End();
		//}

		//Shader Parser Logic
		tApp->Loop();

		// Rendering
		ImGui::Render();
		ImGui_ImplGDI_SetBackgroundColor(&clear_color);
		ImGui_ImplGDI_RenderDrawData(ImGui::GetDrawData());
	}

	// Cleanup
	ImGui_ImplGDI_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	tApp->Finalize();

	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_SIZE:
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
		}
		break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

