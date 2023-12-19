#include "PgApp.h"
#include "ShaderParser.h"
#include "VertexShader.h"
#include "Material.h"
#include "PixelShader.h"
#include "TextHelper.h"
#include "PgDefineEnums.h"

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
	//������ ����� (WinAPI)
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("PgShaderParser"), NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("PgShaderParser"), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	//Window ����.
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	//Shader Parser Ŭ����.
	std::unique_ptr<Pg::PgApp> tApp = std::make_unique<Pg::PgApp>();
	tApp->Initialize();

	// IMGUI Context üũ.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//��ο� ��Ÿ��.
	ImGui::StyleColorsDark();

	//Win32/GDI Fork ���� Init.
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

	//io : body�� touch�ؼ� �����̴� ���� ����.
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	//���� ����.
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
		// IMGUI ������ ����.
		ImGui_ImplGDI_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//Tool Controls
		{
			ImGui::SetNextWindowPos(ImVec2(10.f, 10.f));
			ImGui::SetNextWindowSize(ImVec2(480.f, 200.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::PushFont(smallFont);
			ImGui::Begin(T_KR("�� ��Ʈ�ѷ�"));
			//ImGui::Text(T_KR("�Ķ�� ����"));               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//Render Buttons
			ImGui::PushFont(bigFont);
			if (ImGui::Button(T_KR("���͸��� ����"), ImVec2(150.f, 37.5f)))
			{
				tApp->OpenMaterialButtonPressed();
			}
			ImGui::SameLine();
			if (ImGui::Button(T_KR("����"), ImVec2(150.f, 37.5f)))
			{
				tApp->SaveMaterialButtonPressed();
			}
			ImGui::SameLine();
			if (ImGui::Button(T_KR("�� ���͸���"), ImVec2(150.f, 37.5f)))
			{
				tApp->NewMaterialButtonPressed();
			}
			if (ImGui::Button(T_KR("�ٸ� �̸����� ����"), ImVec2(150.f, 37.5f)))
			{
				tApp->SaveAsMaterialButtonPressed();
			}
			ImGui::SameLine();
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


			std::wstring tCurShaderPathVS = L"���� VS ���� : ";
			if (tApp->GetShaderParser()->GetVertexShader() != nullptr)
			{
				tCurShaderPathVS.append(tApp->GetShaderParser()->GetVertexShader()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurShaderPathVS));

			std::wstring tCurShaderPathPS = L"���� PS ���� : ";
			if (tApp->GetShaderParser()->GetPixelShader() != nullptr)
			{
				tCurShaderPathPS.append(tApp->GetShaderParser()->GetPixelShader()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurShaderPathPS));
			//
			std::wstring tCurMaterialPath = L"���� ���͸��� ���� : ";
			if (tApp->GetShaderParser()->GetMaterial() != nullptr)
			{
				tCurMaterialPath.append(tApp->GetShaderParser()->GetMaterial()->GetFileName());
			}
			ImGui::Text(T_KR_W(tCurMaterialPath));

			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		{
			ImGui::SetNextWindowPos(ImVec2(500.f, 10.f));
			ImGui::SetNextWindowSize(ImVec2(130.f, 200.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("����"));
			ImGui::PushFont(bigFont);

			if (ImGui::Button(T_KR("��ü ����"), ImVec2(100.f, 37.5f)))
			{
				tApp->ResetEditorButtonPressed();
			}
			ImGui::PopFont();
			ImGui::PushFont(smallFont);
			if (ImGui::Button(T_KR("���ؽ� ���̴� ����", ImVec2(100.f, 37.5f))))
			{
				tApp->ResetVertexShaderButtonPressed();
			}
			if (ImGui::Button(T_KR("�ȼ� ���̴� ����", ImVec2(100.f, 37.5f))))
			{
				tApp->ResetPixelShaderButtonPressed();
			}
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
			ImGui::Begin(T_KR("���ؽ� ���̴� �Ķ����"));
			ImGui::PushFont(smallFont);
			ImGui::Text(T_KR("�Ķ�� ����")); // Display some text (you can use a format strings too)


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
			ImGui::Begin(T_KR("�ȼ� ���̴� �Ķ����"));
			ImGui::PushFont(smallFont);
			ImGui::Text(T_KR("�Ķ�� ����")); // Display some text (you can use a format strings too)


			ImGui::PopFont();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		{
			ImGui::SetNextWindowPos(ImVec2(10.f, 220.f));
			ImGui::SetNextWindowSize(ImVec2(620.f, 530.f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, { 0.2f, 0.3f, 0.4f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.1254f,0.698f,0.666f, 1.f });
			ImGui::Begin(T_KR("����"));
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

