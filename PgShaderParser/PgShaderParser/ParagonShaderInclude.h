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
	//ShaderParser에 Static하게 지금 읽는 경로를 가져오면 된다. 함수를 통해서.
	//다만, Relative Path 지원은?

	class ParagonShaderInclude : public ID3DInclude
	{
	public:
		// _shaderDir: 실제로 컴파일하려고 하는 셰이더의 경로
		// _systemDir: 디폴트 셰이더 포함 경로

		ParagonShaderInclude(const char* shaderDir, const char* systemDir) :
			_shaderDir(shaderDir),
			_systemDir(systemDir)
		{
			//
		}

		HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override
		{
			//std::wstring filePath;
			//if (IncludeType == D3D_INCLUDE_LOCAL) //로컬 프로그램 경로
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
