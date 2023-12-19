#pragma once
#include <d3dcommon.h>
#include <d3d11.h>
#include <string>

#include "TextHelper.h"

namespace Pg
{
	//Reference
	//https://www.asawicki.info/news_1515_implementing_id3d10include
	//https://github.com/TheRealMJP/BakingLab/blob/master/SampleFramework11/v1.02/Graphics/ShaderCompilation.cpp#L59
	//https://stackoverflow.com/questions/76262226/hlsl-shaders-compilation-error-failed-to-open-source-file
	//ShaderParser�� Static�ϰ� ���� �д� ��θ� �������� �ȴ�. �Լ��� ���ؼ�.
	//�ٸ�, Relative Path ������?

	class ParagonShaderInclude : public ID3DInclude
	{
	public:
		// _shaderDir: ������ �������Ϸ��� �ϴ� ���̴��� ���
		// _systemDir: ����Ʈ ���̴� ���� ���

		ParagonShaderInclude(const char* shaderDir, const char* systemDir) :
			_shaderDir(shaderDir),
			_systemDir(systemDir)
		{
			//
		}

		HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override
		{
			//std::wstring filePath;
			//if (IncludeType == D3D_INCLUDE_LOCAL) //���� ���α׷� ���
			//{
			//	filePath = TextHelper::AnsiToWString(pFileName);
			//}
			//else if (IncludeType == D3D_INCLUDE_SYSTEM)
			//{
			//	filePath = SampleFrameworkDir() + L"Shaders\\" + AnsiToWString(pFileName);
			//}
			//else
			//	return E_FAIL;
			//
			//if (FileExists(filePath.c_str()) == false)
			//	return E_FAIL;
			//
			//File file(filePath.c_str(), FileOpenMode::Read);
			//*pBytes = UINT(file.Size());
			//uint8* data = reinterpret_cast<uint8*>(std::malloc(*pBytes));
			//file.Read(*pBytes, data);
			//*ppData = data;
			//return S_OK;
		}

		HRESULT Close(LPCVOID pData) override
		{
			std::free(const_cast<void*>(pData));
			return S_OK;
		}

	private:
		std::string _shaderDir;
		std::string _systemDir;
	};

}
