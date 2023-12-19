#include "ShaderParser.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <cassert>

#define DEFAULT_PATH_NULL L"NULL"

namespace Pg
{
	ShaderParser::ShaderParser()
		: _currentVSPath(DEFAULT_PATH_NULL), _currentPSPath(DEFAULT_PATH_NULL), _currentMaterialPath(DEFAULT_PATH_NULL)
	{

	}

	ShaderParser::~ShaderParser()
	{

	}

	void ShaderParser::Initialize()
	{

	}

	void ShaderParser::Finalize()
	{
		ResetAll();
	}

	bool ShaderParser::LoadVertexShader(const std::wstring& shaderPath)
	{
		//������ �ִ� ���� �� ����.
		//Reset();
		//
		////HLSL Compile�ؼ� �о����.
		//HRESULT hr = S_OK;
		//ID3DBlob* tShaderByteCode = nullptr;
		//ID3DBlob* tIfErrorBlob = nullptr;
		//
		////�������ϴ� Flag.
		//UINT tCompileFlags = 0;
		//hr = D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		//	"VS", "vs_5_0", tCompileFlags, 0, &tShaderByteCode, &tIfErrorBlob);
		//assert(SUCCEEDED(hr));
		//
		////���� Reflection D3D �ڵ�.
		//ID3D11ShaderReflection* reflection = nullptr;
		//
		//hr = D3DReflect(tShaderByteCode->GetBufferPointer(), 
		//	tShaderByteCode->GetBufferSize(),
		//	IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&reflection));
		//assert(SUCCEEDED(hr));

		return false;
	}

	bool ShaderParser::LoadPixelShader(const std::wstring& shaderPath)
	{
		return false;
	}

	Pg::Material* ShaderParser::GetMaterial()
	{
		return _material;
	}

	std::wstring ShaderParser::GetCurrentVertexShaderPath()
	{
		return 
	}

	void ShaderParser::ResetAll()
	{
		
	}
}