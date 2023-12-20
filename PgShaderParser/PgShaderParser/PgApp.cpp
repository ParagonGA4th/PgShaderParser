#include "PgApp.h"
#include "ShaderParser.h"

#include "Material.h"
#include "VertexShader.h"
#include "PixelShader.h"
//#include "MaterialPropertyList.h"

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
		// COM ���̺귯�� �ʱ�ȭ
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

	Pg::ShaderParser* PgApp::GetShaderParser()
	{
		return _shaderParser.get();
	}

	void PgApp::OpenShaderButtonPressed(eShaderType shaderType)
	{
		// Common Item Dialog �������̽� ����
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		//������. File Open Dialog ����.
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

		itemDialog->SetTitle(tTitle.c_str()); // ���� ���� (���� ����)

		// ���� ���� ����: .ppt Ȯ���� ����
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Render Shader", L"*.cso" };

		itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		itemDialog->SetFileTypeIndex(1); // �⺻ Ȯ���� ���� (1���� ����)

		// ���� ���� ��ȭ ���� ǥ��
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
		// Common Item Dialog �������̽� ����
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));
		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		itemDialog->SetFileName(L"SavedMaterial.pgmat");

		// ���� ���� ����: .ppt Ȯ���� ����
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

		itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		itemDialog->SetFileTypeIndex(0); // �⺻ Ȯ���� ���� (1���� ����)

		// ���� ���� ��ȭ ���� ǥ��
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

			HANDLE hFile = CreateFile(
				_shaderParser->GetMaterial()->GetFilePath().c_str(),
				GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			_shaderParser->SaveToXMLFile(_shaderParser->GetMaterial()->GetFilePath());
		}

		itemDialog->Release();
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
					//�Ķ���� ���� �ϱ�.
					COMDLG_FILTERSPEC fileTypes[1];

					fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

					pFileSaveDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
					pFileSaveDialog->SetFileTypeIndex(0); // �⺻ Ȯ���� ���� (1���� ����)
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

								///Material �����.
								_shaderParser->CreateMaterial(tFilePath);
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
					//�Ķ���� ���� �ϱ�.
					COMDLG_FILTERSPEC fileTypes[1];

					fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

					pFileSaveDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
					pFileSaveDialog->SetFileTypeIndex(0); // �⺻ Ȯ���� ���� (1���� ����)
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

								///�ߵ� ����, �켱 ���� ����.
								std::ifstream inFile(_shaderParser->GetMaterial()->GetFilePath());
								_shaderParser->CreateMaterial(tFilePath);
								_shaderParser->CopyToXMLFile(tFilePath, inFile);
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

	void PgApp::OpenMaterialButtonPressed()
	{
		// Common Item Dialog �������̽� ����
		HRESULT hr;

		//Windows File Dialog Open
		IFileDialog* itemDialog;

		//������. File Open Dialog ����.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&itemDialog));

		if (FAILED(hr)) { CoUninitialize(); assert(SUCCEEDED(hr)); }

		std::wstring tTitle = L"Choose .pgmat file";

		itemDialog->SetTitle(tTitle.c_str()); // ���� ���� (���� ����)

		// ���� ���� ����: .ppt Ȯ���� ����
		COMDLG_FILTERSPEC fileTypes[1];

		fileTypes[0] = { L"Paragon Material", L"*.pgmat" };

		itemDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
		itemDialog->SetFileTypeIndex(1); // �⺻ Ȯ���� ���� (1���� ����)

		// ���� ���� ��ȭ ���� ǥ��
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