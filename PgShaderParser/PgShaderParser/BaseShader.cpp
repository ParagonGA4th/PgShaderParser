#include "BaseShader.h"
#include "ConstantBufferPropertyList.h"
#include "TexturesPropertyList.h"
#include "D3DHelper.h"

#include <filesystem>
#include <cassert>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3dcommon.h>

#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

namespace Pg
{
	BaseShader::BaseShader(const std::wstring& path) :
		_filePath(path)
	{
		_matPropConstantBufferList = std::make_unique<ConstantBufferPropertyList>();
		LoadReflection();
		GetConstantBufferVariableInfo();
	}

	BaseShader::~BaseShader()
	{

	}

	void BaseShader::LoadReflection()
	{
		//HLSL Compile해서 읽어오기.
		HRESULT hr = S_OK;
		ID3DBlob* tShaderByteCode = nullptr;
		//Blob으로 D3D 파일을 읽어온다. (Load)
		hr = D3DReadFileToBlob(_filePath.c_str(), &tShaderByteCode);
		assert(SUCCEEDED(hr));

		//실제 Reflection D3D 코드.
		hr = D3DReflect(tShaderByteCode->GetBufferPointer(),
			tShaderByteCode->GetBufferSize(),
			IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&_reflection));
		assert(SUCCEEDED(hr));
	}

	std::wstring BaseShader::GetFilePath()
	{
		return _filePath;
	}

	std::wstring BaseShader::GetFileName()
	{
		return std::filesystem::path(_filePath).filename();
	}

	void BaseShader::GetConstantBufferVariableInfo()
	{

		//시스템에서 클라이언트에게 노출된 Register부터 값을 바꿀 수 있게 된다.
		D3D11_SHADER_DESC shaderDesc;
		HR(_reflection->GetDesc(&shaderDesc));
		const UINT totalNumCBuffers = shaderDesc.ConstantBuffers;

		//나중에 파이프라인이 바뀌게 된다면, 여러 개가 가능해질 수도 있음.
		//아니면 디폴트로 적용하는 CBuffer가 있다면, 이 역시 반영되어서 바뀌어야 한다.
		assert(totalNumCBuffers == 1 && "Paragon Engine : 상수 버퍼 하나짜리로 Fix (클라이언트 딴)");

		//Constant Buffer는 하나 가져오는 것으로 하드코딩.
		ID3D11ShaderReflectionConstantBuffer* cbReflection = nullptr;
		cbReflection = _reflection->GetConstantBufferByIndex(0);

		D3D11_SHADER_BUFFER_DESC tConstantBufferDesc;
		HR(cbReflection->GetDesc(&tConstantBufferDesc));

		_matPropConstantBufferList->SetByteCount(tConstantBufferDesc.Size);
		_matPropConstantBufferList->SetConstantBufferName(tConstantBufferDesc.Name);

		for (UINT i = 0; i < tConstantBufferDesc.Variables; i++)
		{
			ID3D11ShaderReflectionVariable* varReflection = cbReflection->GetVariableByIndex(i);

			D3D11_SHADER_VARIABLE_DESC tVarDesc;
			HR(varReflection->GetDesc(&tVarDesc));

			ID3D11ShaderReflectionType* tReflType = varReflection->GetType();
			D3D11_SHADER_TYPE_DESC tTypeDesc;
			HR(tReflType->GetDesc(&tTypeDesc));

			ProcessConstantBufferVariables(&tVarDesc, &tTypeDesc);
		}
	}

	void BaseShader::ProcessConstantBufferVariables(const _D3D11_SHADER_VARIABLE_DESC* shaderVarDesc, const _D3D11_SHADER_TYPE_DESC* shaderTypeDesc)
	{
		assert(shaderTypeDesc->Class == D3D_SVC_SCALAR || shaderTypeDesc->Class == D3D_SVC_VECTOR);
		
		






	}

}
