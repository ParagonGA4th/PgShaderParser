#include "PgApp.h"
#include "ShaderParser.h"

#include "Material.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBufferPropertyList.h"
#include "TexturesPropertyList.h"

#include <shlwapi.h>;
#include <shellapi.h>;
#include <shobjidl.h>
#include <windows.h>


namespace Pg
{
	PgApp::PgApp()
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

		_shaderParser = std::make_unique<ShaderParser>();
	}

	void PgApp::Loop()
	{

	}

	void PgApp::Finalize()
	{
		CoUninitialize();
	}

	void PgApp::DisplayIMGUIConstantBufferData(ImFont* bigFont, ConstantBufferPropertyList* tConstantBufferList)
	{
		if (!tConstantBufferList->_boolPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Boolean>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_boolPropList.size(); i++)
		{
			ImGui::Checkbox(tConstantBufferList->_boolPropList[i].first._name.c_str(), &(tConstantBufferList->_boolPropList[i].second));
		}

		if (!tConstantBufferList->_uintPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Unsigned Int>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_uintPropList.size(); i++)
		{
			int tUInt = tConstantBufferList->_uintPropList[i].second;
			ImGui::InputInt(tConstantBufferList->_uintPropList[i].first._name.c_str(), &tUInt);
			tConstantBufferList->_uintPropList[i].second = std::clamp(tUInt, 0, INT_MAX);
		}

		if (!tConstantBufferList->_intPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Int>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_intPropList.size(); i++)
		{
			ImGui::InputInt(tConstantBufferList->_intPropList[i].first._name.c_str(), &(tConstantBufferList->_intPropList[i].second));
		}

		if (!tConstantBufferList->_floatPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Float>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_floatPropList.size(); i++)
		{
			ImGui::InputFloat(tConstantBufferList->_floatPropList[i].first._name.c_str(), &(tConstantBufferList->_floatPropList[i].second));
		}

		if (!tConstantBufferList->_vec2PropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Vector2>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_vec2PropList.size(); i++)
		{
			ImGui::InputFloat2(tConstantBufferList->_vec2PropList[i].first._name.c_str(), tConstantBufferList->_vec2PropList[i].second._v);
		}

		if (!tConstantBufferList->_vec3PropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Vector3>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_vec3PropList.size(); i++)
		{
			ImGui::InputFloat3(tConstantBufferList->_vec3PropList[i].first._name.c_str(), tConstantBufferList->_vec3PropList[i].second._v);
		}

		if (!tConstantBufferList->_vec4PropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Vector4 / Color4>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tConstantBufferList->_vec4PropList.size(); i++)
		{
			ImGui::InputFloat4(tConstantBufferList->_vec4PropList[i].first._name.c_str(), tConstantBufferList->_vec4PropList[i].second._v);
		}
	}

	void PgApp::DisplayIMGUITextureData(ImFont* bigFont, TexturesPropertyList* tTexturesBufferList)
	{
		if (!tTexturesBufferList->_texture1DPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Texture1D>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tTexturesBufferList->_texture1DPropList.size(); i++)
		{
			ImGui::InputText(tTexturesBufferList->_texture1DPropList[i].first._name.c_str(), &tTexturesBufferList->_texture1DPropList[i].second);
		}

		if (!tTexturesBufferList->_texture2DPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Texture2D>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tTexturesBufferList->_texture2DPropList.size(); i++)
		{
			ImGui::InputText(tTexturesBufferList->_texture2DPropList[i].first._name.c_str(), &tTexturesBufferList->_texture2DPropList[i].second);
		}

		if (!tTexturesBufferList->_texture2DArrayPropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<Texture2DArray>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tTexturesBufferList->_texture2DArrayPropList.size(); i++)
		{
			ImGui::InputText(tTexturesBufferList->_texture2DArrayPropList[i].first._name.c_str(), &tTexturesBufferList->_texture2DArrayPropList[i].second);
		}

		if (!tTexturesBufferList->_textureCubePropList.empty())
		{
			ImGui::PushFont(bigFont);
			ImGui::Text("<TextureCube>");
			ImGui::PopFont();
		}
		for (size_t i = 0; i < tTexturesBufferList->_textureCubePropList.size(); i++)
		{
			ImGui::InputText(tTexturesBufferList->_textureCubePropList[i].first._name.c_str(), &tTexturesBufferList->_textureCubePropList[i].second);
		}
	}

	Pg::ShaderParser* PgApp::GetShaderParser()
	{
		return _shaderParser.get();
	}

	void PgApp::OpenShaderButtonPressed(eShaderType shaderType)
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
		std::wstring tTitle = L"Choose .cso file";
		tTitle.append(tShaderStr);
		tTitle.append(L"to base off of.");

		itemDialog->SetTitle(tTitle.c_str()); // 제목 설정 (선택 사항)

		// 파일 필터 설정: .ppt 확장자 필터
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Render Shader", L"*.cso" };

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

		///
		if (filePath != NULL)
		{
			std::wstring wString;
			wString = filePath;

			if (shaderType == eShaderType::_VS)
			{
				_shaderParser->CreateVertexShader(wString);
			}
			else if (shaderType == eShaderType::_PS)
			{
				_shaderParser->CreatePixelShader(wString);
			}
		}

		itemDialog->Release();
	}

	void PgApp::SaveMaterialButtonPressed()
	{
		assert(false && "아직 준비되지 않음");
		//// Common Item Dialog 인터페이스 생성
		//HRESULT hr;

		////Windows File Dialog Open
		//IFileDialog* itemDialog;

		//hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));
		//if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		//itemDialog->SetFileName(L"SavedMaterial.pgmat");

		//// 파일 필터 설정: .ppt 확장자 필터
		//COMDLG_FILTERSPEC fileTypes[1];

		//fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

		//itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		//itemDialog->SetFileTypeIndex(0); // 기본 확장자 선택 (1부터 시작)

		//// 파일 저장 대화 상자 표시
		//hr = itemDialog->Show(NULL);
		//IShellItem* pItem;
		//LPWSTR filePath = NULL;

		//if (SUCCEEDED(hr))
		//{
		//	hr = itemDialog->GetResult(&pItem);
		//	if (SUCCEEDED(hr))
		//	{
		//		hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
		//		if (SUCCEEDED(hr)) CoTaskMemFree(filePath);
		//		pItem->Release();
		//	}
		//}

		//if (filePath != NULL)
		//{
		//	std::wstring wString;
		//	wString = filePath;

		//	HANDLE hFile = CreateFile(
		//		_shaderParser->GetMaterial()->GetFilePath().c_str(),
		//		GENERIC_WRITE,
		//		0,
		//		NULL,
		//		CREATE_ALWAYS,
		//		FILE_ATTRIBUTE_NORMAL,
		//		NULL
		//	);

		//	_shaderParser->SaveToXMLFile(_shaderParser->GetMaterial()->GetFilePath());
		//}

		//itemDialog->Release();
	}

	void PgApp::NewMaterialButtonPressed()
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
								
								//.pgmat이 없으면 넣어준다.
								auto n = tFilePath.find(L".pgmat");
								if (n == std::string::npos)
								{
									tFilePath.append(L".pgmat");
								}
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

								///Material 만들기.
								if (_shaderParser->GetPixelShader() != nullptr && _shaderParser->GetVertexShader() != nullptr)
								{
									_shaderParser->CreateNewMaterial(tFilePath);
								}
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

	void PgApp::SaveAsMaterialButtonPressed()
	{
		assert(false && "아직 준비되지 않음");
		//// Create the File Open Dialog object
		//IFileSaveDialog* pFileSaveDialog;
		//HRESULT hr = CoCreateInstance(
		//	CLSID_FileSaveDialog,
		//	NULL,
		//	CLSCTX_INPROC_SERVER,
		//	IID_PPV_ARGS(&pFileSaveDialog)
		//);

		//if (SUCCEEDED(hr)) {
		//	// Set options for the File Save Dialog
		//	DWORD dwFlags;
		//	hr = pFileSaveDialog->GetOptions(&dwFlags);

		//	if (SUCCEEDED(hr)) {
		//		// Set the options to include the "OverwritePrompt" flag
		//		hr = pFileSaveDialog->SetOptions(dwFlags | FOS_OVERWRITEPROMPT);

		//		if (SUCCEEDED(hr)) {
		//			///
		//			//파라미터 고르게 하기.
		//			COMDLG_FILTERSPEC fileTypes[1];

		//			fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

		//			pFileSaveDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		//			pFileSaveDialog->SetFileTypeIndex(0); // 기본 확장자 선택 (1부터 시작)
		//			///
		//			// Show the File Save Dialog
		//			hr = pFileSaveDialog->Show(NULL);

		//			if (SUCCEEDED(hr)) {
		//				// Get the selected folder and file name
		//				IShellItem* pShellItem;
		//				hr = pFileSaveDialog->GetResult(&pShellItem);

		//				if (SUCCEEDED(hr)) {
		//					PWSTR pszFolderPath;
		//					hr = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);

		//					if (SUCCEEDED(hr)) {
		//						// Combine the folder path and file name
		//						std::wstring tFilePath = pszFolderPath;
		//						assert(tFilePath.size() < MAX_PATH);
		//						tFilePath.append(L".pgmat");
		//						//PathCombine(szFilePath, pszFolderPath, szFileName);

		//						// Create the new text file
		//						HANDLE hFile = CreateFile(
		//							tFilePath.c_str(),
		//							GENERIC_WRITE,
		//							0,
		//							NULL,
		//							CREATE_ALWAYS,
		//							FILE_ATTRIBUTE_NORMAL,
		//							NULL
		//						);

		//						if (hFile == INVALID_HANDLE_VALUE) {
		//							wprintf(L"Error creating file: %d\n", GetLastError());
		//						}
		//						// Close the file handle
		//						CloseHandle(hFile);

		//						// Release the allocated memory
		//						CoTaskMemFree(pszFolderPath);

		//						///발동 전에, 우선 정보 저장.
		//						std::ifstream inFile(_shaderParser->GetMaterial()->GetFilePath());
		//						_shaderParser->CreateMaterial(tFilePath);
		//						_shaderParser->CopyToXMLFile(tFilePath, inFile);
		//					}

		//					// Release the IShellItem
		//					pShellItem->Release();
		//				}
		//			}
		//		}
		//	}
		//}
		//// Release the File Save Dialog
		//pFileSaveDialog->Release();
	}

	void PgApp::OpenMaterialButtonPressed()
	{
		assert(false && "아직 구현되지 않음");
		/*
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
			_shaderParser->CreateMaterial(wString);
		}

		itemDialog->Release();
		*/
	}

	void PgApp::ResetEditorButtonPressed()
	{
		_shaderParser->ResetAll();
	}

	void PgApp::ResetVertexShaderButtonPressed()
	{
		_shaderParser->ResetVertexShader();
	}

	void PgApp::ResetPixelShaderButtonPressed()
	{
		_shaderParser->ResetPixelShader();
	}

	std::wstring PgApp::GetVSName()
	{
		if (_shaderParser->GetVertexShader())
		{
			return _shaderParser->GetVertexShader()->GetFileName();
		}
		else
		{
			return DEFAULT_PATH_NULL;
		}
	}

	std::wstring PgApp::GetPSName()
	{
		if (_shaderParser->GetPixelShader())
		{
			return _shaderParser->GetPixelShader()->GetFileName();
		}
		else
		{
			return DEFAULT_PATH_NULL;
		}
	}

	std::wstring PgApp::GetMaterialName()
	{
		if (_shaderParser->GetMaterial())
		{
			_shaderParser->GetMaterial()->GetFileName();
		}
		else
		{
			return DEFAULT_PATH_NULL;
		}
	}
}