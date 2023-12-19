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
		//HLSL Compile�ؼ� �о����.
		HRESULT hr = S_OK;
		ID3DBlob* tShaderByteCode = nullptr;
		ID3DBlob* tIfErrorBlob = nullptr;

		//�������ϴ� Flag.
		UINT tCompileFlags = 0;

		//������ Shader�� Entry Point = main�� �Ǿ�� �Ѵ�.
		hr = D3DCompileFromFile(_filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "ps_5_0", tCompileFlags, 0, &tShaderByteCode, &tIfErrorBlob);

		if (FAILED(hr))
		{
			std::string error = (char*)tIfErrorBlob->GetBufferPointer();
			printf(error.c_str());
			assert(false);
		}

		//���� Reflection D3D �ڵ�.
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