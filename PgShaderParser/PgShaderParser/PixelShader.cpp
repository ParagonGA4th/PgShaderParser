#include "PixelShader.h"
#include "MaterialPropertyList.h"
#include <filesystem>
#include <cassert>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>

#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

namespace Pg
{
	PixelShader::PixelShader(const std::wstring& path) :
		_filePath(path)
	{
		_matPropList = std::make_unique<MaterialPropertyList>();
		LoadReflection();
	}

	PixelShader::~PixelShader()
	{

	}

	void PixelShader::LoadReflection()
	{
		//HLSL Compile해서 읽어오기.
		HRESULT hr = S_OK;
		ID3DBlob* tShaderByteCode = nullptr;
		ID3DBlob* tIfErrorBlob = nullptr;

		//컴파일하는 Flag.
		UINT tCompileFlags = 0;

		//무조건 Shader의 Entry Point = main이 되어야 한다.
		hr = D3DCompileFromFile(_filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "ps_5_0", tCompileFlags, 0, &tShaderByteCode, &tIfErrorBlob);

		if (FAILED(hr))
		{
			std::string error = (char*)tIfErrorBlob->GetBufferPointer();
			printf(error.c_str());
			assert(false);
		}

		//실제 Reflection D3D 코드.
		hr = D3DReflect(tShaderByteCode->GetBufferPointer(),
			tShaderByteCode->GetBufferSize(),
			IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&_reflection));
		assert(SUCCEEDED(hr));
	}

	std::wstring PixelShader::GetFilePath()
	{
		return _filePath;
	}

	std::wstring PixelShader::GetFileName()
	{
		return std::filesystem::path(_filePath).filename();
	}

}