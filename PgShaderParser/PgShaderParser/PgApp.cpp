#include "PgApp.h"
#include "ShaderParser.h"

namespace Pg
{
	PgApp::PgApp() 
		: _currentVSPath(L"Default_VSPath"), _currentPSPath(L"Default_PSPath"), _currentMaterialPath(L"DefaultMaterialPath")
	{
		
	}

	PgApp::~PgApp()
	{

	}

	void PgApp::Initialize()
	{
		// COM 라이브러리 초기화
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		assert(SUCCEEDED(hr));
	}

	void PgApp::Loop()
	{
		
	}

	void PgApp::Finalize()
	{
		CoUninitialize();
	}

	void PgApp::OpenFileButtonPressed(eShaderType shaderType)
	{
		ShowOpenFileDialog(shaderType);
	}

	void PgApp::SaveFileButtonPressed()
	{
		ShowSaveFileDialog();
	}

	void PgApp::NewFileButtonPressed()
	{
		ShowNewFileDialog();
	}

	void PgApp::ShowOpenFileDialog(eShaderType shaderType)
	{
		// Common Item Dialog 인터페이스 생성
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		//열렸음. File Open Dialog 열기.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));
	
		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		itemDialog->SetTitle(L"Choose .hlsl file (RenderShader) to base off of."); // 제목 설정 (선택 사항)
		
		// 파일 필터 설정: .ppt 확장자 필터
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Render Shader", L"*.hlsl" };

		itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		itemDialog->SetFileTypeIndex(1); // 기본 확장자 선택 (1부터 시작)

		// 파일 저장 대화 상자 표시
		hr = itemDialog->Show(NULL);
		IShellItem* pItem;
		LPWSTR filePath = NULL;

		if (SUCCEEDED(hr))
		{
			hr = itemDialog->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
				if (SUCCEEDED(hr)) CoTaskMemFree(filePath);
				pItem->Release();
			}
		}

		if (filePath != NULL)
		{
			std::wstring wString;
			wString.append(&filePath[0]);

			if (shaderType == eShaderType::_VS)
			{
				_currentVSPath.clear();
				_currentVSPath.append(wString);
			}
			else if (shaderType == eShaderType::_PS)
			{
				_currentPSPath.clear();
				_currentPSPath.append(wString));
			}
		}

		itemDialog->Release();
	}

	void PgApp::ShowSaveFileDialog()
	{
		// Common Item Dialog 인터페이스 생성
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));
		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		itemDialog->SetFileName(L"NewMaterial.pgmat");

		// 파일 필터 설정: .ppt 확장자 필터
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

		itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		itemDialog->SetFileTypeIndex(0); // 기본 확장자 선택 (1부터 시작)

		// 파일 저장 대화 상자 표시
		hr = itemDialog->Show(NULL);
		IShellItem* pItem;
		LPWSTR filePath = NULL;

		if (SUCCEEDED(hr))
		{
			hr = itemDialog->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
				if (SUCCEEDED(hr)) CoTaskMemFree(filePath);
				pItem->Release();
			}
		}

		if (filePath != NULL)
		{
			std::wstring wString;
			wString.append(&filePath[0]);

			_currentMaterialPath.clear();
			_currentMaterialPath.append(wString.begin(), wString.end());
		}

		itemDialog->Release();
	}

	void PgApp::ShowNewFileDialog()
	{
		
	}

}