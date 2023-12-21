#include "BaseShader.h"
#include "ConstantBufferPropertyList.h"
#include "TexturesPropertyList.h"
#include "D3DHelper.h"
#include "PgDefineEnums.h"

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
		_matPropTexturesList = std::make_unique<TexturesPropertyList>();
		LoadReflection();
		GetConstantBufferVariableInfo();
		GetTextureBufferVariableInfo();
		assert("");
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
		assert((shaderTypeDesc->Class == D3D_SVC_SCALAR || shaderTypeDesc->Class == D3D_SVC_VECTOR)
			&& "서포트되는 변수 형식이 아님.");

		UINT tCount = shaderTypeDesc->Columns;
		assert(tCount >= 1 && "아니면 카운트가 0개이다.");

		ConstantBufferVariableProp tProp;
		tProp._name = shaderVarDesc->Name;
		tProp._size = shaderVarDesc->Size;
		tProp._startOffset = shaderVarDesc->StartOffset;

		if (shaderTypeDesc->Type == D3D_SVT_BOOL && tCount == 1)
		{
			_matPropConstantBufferList->_boolPropList.push(std::make_pair(tProp, false));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_UINT && tCount == 1)
		{
			_matPropConstantBufferList->_uintPropList.push(std::make_pair(tProp, 0));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_INT && tCount == 1)
		{
			_matPropConstantBufferList->_intPropList.push(std::make_pair(tProp, 0));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 1)
		{
			_matPropConstantBufferList->_floatPropList.push(std::make_pair(tProp, 0.f));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 2)
		{
			_matPropConstantBufferList->_vec2PropList.push(std::make_pair(tProp, float2{ 0.f,0.f }));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 3)
		{
			_matPropConstantBufferList->_vec3PropList.push(std::make_pair(tProp, float3{ 0.f,0.f,0.f }));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 4)
		{
			_matPropConstantBufferList->_vec4PropList.push(std::make_pair(tProp, float4{ 0.f,0.f,0.f,0.f }));
		}
		else
		{
			assert(false && "호환되지 않는 형식의 Variable.");
		}
	}

	void BaseShader::GetTextureBufferVariableInfo()
	{
		//시스템에서 클라이언트에게 노출된 Register부터 값을 바꿀 수 있게 된다.
		D3D11_SHADER_DESC shaderDesc;
		HR(_reflection->GetDesc(&shaderDesc));
		
		for (unsigned int i = 0; i < shaderDesc.BoundResources; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC tBindDesc;
			_reflection->GetResourceBindingDesc(i, &tBindDesc);

			switch (tBindDesc.Type)
			{
				case D3D_SIT_TEXTURE:
				{
					if (tBindDesc.BindPoint >= TEXTURES_CLIENT_START_REGISTER)
					{
						TexturesVariableProp tProp;
						tProp._name = tBindDesc.Name;
						tProp._registerCnt = tBindDesc.BindPoint;
						if (SUPPORTED_MIN_TEXTURE_RETURN_TYPE_ENUM <= tBindDesc.ReturnType &&
							SUPPORTED_MAX_TEXTURE_RETURN_TYPE_ENUM >= tBindDesc.ReturnType)
						{
							tProp._resReturnType = static_cast<eResourceReturnType>(tBindDesc.ReturnType);
						}
						else
						{
							assert(false && "Unsupported Format");
						}

						//이제 각각 어떤 타입인지 골라내야 한다.
						if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE1D)
						{
							_matPropTexturesList->_texture1DPropList.push(std::make_pair(tProp,"TextureName"));
						}
						else if(tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE2D)
						{
							_matPropTexturesList->_texture2DPropList.push(std::make_pair(tProp, "TextureName"));
						}
						else if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE2DARRAY)
						{
							_matPropTexturesList->_texture2DArrayPropList.push(std::make_pair(tProp, "TextureName"));
						}
						else if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURECUBE)
						{
							_matPropTexturesList->_textureCubePropList.push(std::make_pair(tProp, "TextureName"));
						}
						else
						{
							assert(false && "Unsupported Resource Dimension");
						}
					}
				}
				break;
				default: 
				break; //샘플러와 다른 리소스 타입들은, 이미 만들어진 목록에서 고를 수 있을 것이다.
			}
		}
	}
}
