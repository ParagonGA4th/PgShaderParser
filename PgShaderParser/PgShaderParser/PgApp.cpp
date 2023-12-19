#include "PgApp.h"
#include "ShaderParser.h"

#include <shlwapi.h>;
#include <shellapi.h>;
#include <shobjidl.h>
#include <windows.h>

#define DEFAULT_PATH_NULL L"NULL"
namespace Pg
{
	PgApp::PgApp()
		: _currentVSPath(DEFAULT_PATH_NULL), _currentPSPath(DEFAULT_PATH_NULL), _currentMaterialPath(DEFAULT_PATH_NULL)
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

	void PgApp::OpenShaderButtonPressed(eShaderType shaderType)
	{
		ShowOpenShaderDialog(shaderType);
	}

	void PgApp::SaveMaterialButtonPressed()
	{
		ShowSaveMaterialDialog();
	}

	void PgApp::NewMaterialButtonPressed()
	{
		ShowNewMaterialDialog();
	}

	void PgApp::SaveAsMaterialButtonPressed()
	{
		ShowSaveAsMaterialDialog();
	}

	void PgApp::OpenMaterialButtonPressed()
	{
		ShowOpenMaterialDialog();
	}

	void PgApp::ResetEditorButtonPressed()
	{
		ResetEditor();
	}

	void PgApp::ResetVertexShaderButtonPressed()
	{
		ResetVS();
	}

	void PgApp::ResetPixelShaderButtonPressed()
	{
		ResetPS();
	}

	void PgApp::ShowOpenShaderDialog(eShaderType shaderType)
	{
		// Common Item Dialog 인터페이스 생성
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		//열렸음. File Open Dialog 열기.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));

		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		std::wstring tShaderStr = L"";
		if (shaderType == eShaderType::_VS)
		{
			tShaderStr = L" (Vertex Shader) ";
		}
		if (shaderType == eShaderType::_PS)
		{
			tShaderStr = L" (Pixel Shader) ";
		}
		std::wstring tTitle = L"Choose .hlsl file";
		tTitle.append(tShaderStr);
		tTitle.append(L"to base off of.");

		itemDialog->SetTitle(tTitle.c_str()); // 제목 설정 (선택 사항)

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
			wString = filePath;

			if (shaderType == eShaderType::_VS)
			{
				_currentVSPath.clear();
				_currentVSPath.append(wString);
			}
			else if (shaderType == eShaderType::_PS)
			{
				_currentPSPath.clear();
				_currentPSPath.append(wString);
			}
		}

		itemDialog->Release();
	}

	void PgApp::ShowSaveMaterialDialog()
	{
		// Common Item Dialog 인터페이스 생성
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));
		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		itemDialog->SetFileName(L"SavedMaterial.pgmat");

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
			wString = filePath;

			_currentMaterialPath.clear();
			_currentMaterialPath.append(wString);

			HANDLE hFile = CreateFile(
				_currentMaterialPath.c_str(),
				GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
		}

		itemDialog->Release();
	}

	void PgApp::ShowNewMaterialDialog()
	{
		// Create the File Open Dialog object
		IFileSaveDialog* pFileSaveDialog;
		HRESULT hr = CoCreateInstance(
			CLSID_FileSaveDialog,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pFileSaveDialog)
		);

		if (SUCCEEDED(hr)) {
			// Set options for the File Save Dialog
			DWORD dwFlags;
			hr = pFileSaveDialog->GetOptions(&dwFlags);

			if (SUCCEEDED(hr)) {
				// Set the options to include the "OverwritePrompt" flag
				hr = pFileSaveDialog->SetOptions(dwFlags | FOS_OVERWRITEPROMPT);

				if (SUCCEEDED(hr)) {
					///
					//파라미터 고르게 하기.
					COMDLG_FILTERSPEC fileTypes[1];

					fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

					pFileSaveDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
					pFileSaveDialog->SetFileTypeIndex(0); // 기본 확장자 선택 (1부터 시작)
					///
					// Show the File Save Dialog
					hr = pFileSaveDialog->Show(NULL);

					if (SUCCEEDED(hr)) {
						// Get the selected folder and file name
						IShellItem* pShellItem;
						hr = pFileSaveDialog->GetResult(&pShellItem);

						if (SUCCEEDED(hr)) {
							PWSTR pszFolderPath;
							hr = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);

							if (SUCCEEDED(hr)) {
								// Combine the folder path and file name
								std::wstring tFilePath = pszFolderPath;
								assert(tFilePath.size() < MAX_PATH);
								tFilePath.append(L".pgmat");
								//PathCombine(szFilePath, pszFolderPath, szFileName);

								// Create the new text file
								HANDLE hFile = CreateFile(
									tFilePath.c_str(),
									GENERIC_WRITE,
									0,
									NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL
								);

								if (hFile == INVALID_HANDLE_VALUE) {
									wprintf(L"Error creating file: %d\n", GetLastError());
								}
								// Close the file handle
								CloseHandle(hFile);

								// Release the allocated memory
								CoTaskMemFree(pszFolderPath);

								_currentMaterialPath = tFilePath;
							}

							// Release the IShellItem
							pShellItem->Release();
						}
					}
				}
			}

			// Release the File Save Dialog
			pFileSaveDialog->Release();
		}
	}

	void PgApp::ShowSaveAsMaterialDialog()
	{
		// Create the File Open Dialog object
		IFileSaveDialog* pFileSaveDialog;
		HRESULT hr = CoCreateInstance(
			CLSID_FileSaveDialog,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pFileSaveDialog)
		);

		if (SUCCEEDED(hr)) {
			// Set options for the File Save Dialog
			DWORD dwFlags;
			hr = pFileSaveDialog->GetOptions(&dwFlags);

			if (SUCCEEDED(hr)) {
				// Set the options to include the "OverwritePrompt" flag
				hr = pFileSaveDialog->SetOptions(dwFlags | FOS_OVERWRITEPROMPT);

				if (SUCCEEDED(hr)) {
					///
					//파라미터 고르게 하기.
					COMDLG_FILTERSPEC fileTypes[1];

					fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

					pFileSaveDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
					pFileSaveDialog->SetFileTypeIndex(0); // 기본 확장자 선택 (1부터 시작)
					///
					// Show the File Save Dialog
					hr = pFileSaveDialog->Show(NULL);

					if (SUCCEEDED(hr)) {
						// Get the selected folder and file name
						IShellItem* pShellItem;
						hr = pFileSaveDialog->GetResult(&pShellItem);

						if (SUCCEEDED(hr)) {
							PWSTR pszFolderPath;
							hr = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);

							if (SUCCEEDED(hr)) {
								// Combine the folder path and file name
								std::wstring tFilePath = pszFolderPath;
								assert(tFilePath.size() < MAX_PATH);
								tFilePath.append(L".pgmat");
								//PathCombine(szFilePath, pszFolderPath, szFileName);

								// Create the new text file
								HANDLE hFile = CreateFile(
									tFilePath.c_str(),
									GENERIC_WRITE,
									0,
									NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL
								);

								if (hFile == INVALID_HANDLE_VALUE) {
									wprintf(L"Error creating file: %d\n", GetLastError());
								}
								// Close the file handle
								CloseHandle(hFile);

								// Release the allocated memory
								CoTaskMemFree(pszFolderPath);

								_currentMaterialPath = tFilePath;
							}

							// Release the IShellItem
							pShellItem->Release();
						}
					}
				}
			}
		}
		// Release the File Save Dialog
		pFileSaveDialog->Release();
	}

	void PgApp::ShowOpenMaterialDialog()
	{
		// Common Item Dialog 인터페이스 생성
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		//열렸음. File Open Dialog 열기.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));

		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		std::wstring tTitle = L"Choose .pgmat file";

		itemDialog->SetTitle(tTitle.c_str()); // 제목 설정 (선택 사항)

		// 파일 필터 설정: .ppt 확장자 필터
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

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
			wString = filePath;
			_currentMaterialPath = wString;
		}

		itemDialog->Release();
	}

	void PgApp::ResetEditor()
	{
		_currentVSPath = DEFAULT_PATH_NULL;
		_currentPSPath = DEFAULT_PATH_NULL;
		_currentMaterialPath = DEFAULT_PATH_NULL;

		_isNowAffectVertexShader = false;
		_isNowAffectPixelShader = false;
		_isNowAffectMaterial = false;
	}

	void PgApp::ResetVS()
	{
		_currentVSPath = DEFAULT_PATH_NULL;
		_isNowAffectVertexShader = false;
	}

	void PgApp::ResetPS()
	{
		_currentPSPath = DEFAULT_PATH_NULL;
		_isNowAffectPixelShader = false;
	}

}