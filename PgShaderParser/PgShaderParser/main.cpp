#include "PgApp.h"
#include "ShaderParser.h"
#include "VertexShader.h"
#include "Material.h"
#include "PixelShader.h"
#include "TextHelper.h"
#include "PgDefineEnums.h"
#include "ConstantBufferPropertyList.h"
#include "TexturesPropertyList.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_gdi.h"

#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <memory>
#include <dinput.h>
#include <tchar.h>
#include <algorithm>


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

	//for (int i = ImGui::ImGuiKey_NamedKey_BEGIN; i<)

	//어두운 스타일.
	ImGui::StyleColorsDark();

	//Win32/GDI Fork 버전 Init.
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplGDI_Init();

	//Pretendard Font Loading.
	ImFont* smallFont = io.Fonts->AddFontFromFileTTF("../Fonts/Pretendard-Medium.ttf", 18.0f, NULL,
		io.Fonts->GetGlyphRangesKorean());
	IM_ASSERT(smallFont != NULL);

	ImFont* bigFont = io.Fonts->AddFontFromFileTTF("../Fonts/Pretendard-Medium.ttf", 23.0f, NULL,
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

		{
			ImGui::SetNextWindowPos(ImVec2(500.f, 10.f));
			ImGui::SetNextWindowSize(ImVec2(130.f, 200.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("조작"));
			ImGui::PushFont(bigFont);
			if (ImGui::Button(T_KR("전체 리셋"), ImVec2(100.f, 37.5f)))
			{
				tApp->ResetEditorButtonPressed();
			}
			ImGui::PopFont();
			ImGui::PushFont(smallFont);
			if (ImGui::Button(T_KR("버텍스 셰이더 리셋", ImVec2(100.f, 37.5f))))
			{
				tApp->ResetVertexShaderButtonPressed();
			}
			if (ImGui::Button(T_KR("픽셀 셰이더 리셋", ImVec2(100.f, 37.5f))))
			{
				tApp->ResetPixelShaderButtonPressed();
			}
			ImGui::PopFont();

			//ImGui::PushFont(bigFont);
			//ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.2f, 0.1f, 1.f });
			//if (ImGui::Button(T_KR("매터리얼 생성"), ImVec2(120.f, 37.5f)))
			//{
			//	//tApp->ResetEditorButtonPressed();
			//}
			//ImGui::PopFont();
			//ImGui::PopStyleColor();

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		//Tool Controls
		{
			ImGui::SetNextWindowPos(ImVec2(10.f, 10.f));
			ImGui::SetNextWindowSize(ImVec2(480.f, 200.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::PushFont(smallFont);
			ImGui::Begin(T_KR("툴 컨트롤러"));
			//ImGui::Text(T_KR("파라곤 엔진"));               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Another Window", &show_another_window);

			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//Render Buttons
			ImGui::PushFont(bigFont);
			//if (ImGui::Button(T_KR("매터리얼 열기"), ImVec2(150.f, 37.5f)))
			//{
			//	tApp->OpenMaterialButtonPressed();
			//}
			//ImGui::SameLine();
			if (ImGui::Button(T_KR("저장"), ImVec2(150.f, 37.5f)))
			{
				tApp->NewMaterialButtonPressed();
			}
			ImGui::SameLine();
			//if (ImGui::Button(T_KR("새 매터리얼"), ImVec2(150.f, 37.5f)))
			//{
			//	tApp->NewMaterialButtonPressed();
			//}
			//if (ImGui::Button(T_KR("다른 이름으로 저장"), ImVec2(150.f, 37.5f)))
			//{
			//	tApp->SaveAsMaterialButtonPressed();
			//}
			//ImGui::SameLine();
			if (ImGui::Button("Vertex Shader", ImVec2(150.f, 37.5f)))
			{
				tApp->OpenShaderButtonPressed(Pg::eShaderType::_VS);
			}
			ImGui::SameLine();
			if (ImGui::Button("Pixel Shader", ImVec2(150.f, 37.5f)))
			{
				tApp->OpenShaderButtonPressed(Pg::eShaderType::_PS);
			}
			ImGui::PopFont();


			std::wstring tCurShaderPathVS = L"현재 VS 파일 : ";
			if (tApp->GetShaderParser()->GetVertexShader() != nullptr)
			{
				tCurShaderPathVS.append(tApp->GetShaderParser()->GetVertexShader()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurShaderPathVS));

			std::wstring tCurShaderPathPS = L"현재 PS 파일 : ";
			if (tApp->GetShaderParser()->GetPixelShader() != nullptr)
			{
				tCurShaderPathPS.append(tApp->GetShaderParser()->GetPixelShader()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurShaderPathPS));
			//
			std::wstring tCurMaterialPath = L"현재 매터리얼 파일 : ";
			if (tApp->GetShaderParser()->GetMaterial() != nullptr)
			{
				tCurMaterialPath.append(tApp->GetShaderParser()->GetMaterial()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurMaterialPath));

			//Alpha Mapping 쓸건지 체크리스트
			ImGui::Checkbox("Use Alpha Blending/Transparency", tApp->GetShaderParser()->GetIsUseAlphaBlendingPointer());

			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		if (tApp->GetShaderParser()->GetVertexShader() != nullptr)
		{
			ImGui::SetNextWindowPos(ImVec2(640.f, 10.f));
			ImGui::SetNextWindowSize(ImVec2(600.f, 350.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("버텍스 셰이더 파라미터"));
			ImGui::PushFont(smallFont);
			//ImGui::Text(T_KR("파라곤 엔진")); // Display some text (you can use a format strings too)

			auto& tConstantBufferList = tApp->GetShaderParser()->GetVertexShader()->_matPropConstantBufferList;
			//Vertex Shader의 프로퍼티 출력.
			tApp->DisplayIMGUIConstantBufferData(bigFont, tConstantBufferList.get());

			auto& tTextureBufferList = tApp->GetShaderParser()->GetVertexShader()->_matPropTexturesList;
			tApp->DisplayIMGUITextureData(bigFont, tTextureBufferList.get());

			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		if (tApp->GetShaderParser()->GetPixelShader() != nullptr)
		{
			ImGui::SetNextWindowPos(ImVec2(640.f, 370.f));
			ImGui::SetNextWindowSize(ImVec2(600.f, 380.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("픽셀 셰이더 파라미터"));
			ImGui::PushFont(smallFont);
			//ImGui::Text(T_KR("파라곤 엔진")); // Display some text (you can use a format strings too)

			auto& tConstantBufferList = tApp->GetShaderParser()->GetPixelShader()->_matPropConstantBufferList;

			//Vertex Shader의 프로퍼티 출력.
			tApp->DisplayIMGUIConstantBufferData(bigFont, tConstantBufferList.get());

			auto& tTextureBufferList = tApp->GetShaderParser()->GetPixelShader()->_matPropTexturesList;
			tApp->DisplayIMGUITextureData(bigFont, tTextureBufferList.get());

			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		if (tApp->GetShaderParser()->GetMaterial() != nullptr)
		{
			ImGui::SetNextWindowPos(ImVec2(10.f, 220.f));
			ImGui::SetNextWindowSize(ImVec2(620.f, 530.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("매터리얼"));
			ImGui::PushFont(smallFont);

			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}
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

