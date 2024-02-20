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
		//HLSL Compile�ؼ� �о����.
		HRESULT hr = S_OK;
		ID3DBlob* tShaderByteCode = nullptr;
		//Blob���� D3D ������ �о�´�. (Load)
		hr = D3DReadFileToBlob(_filePath.c_str(), &tShaderByteCode);
		assert(SUCCEEDED(hr));

		//���� Reflection D3D �ڵ�.
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

		//�ý��ۿ��� Ŭ���̾�Ʈ���� ����� Register���� ���� �ٲ� �� �ְ� �ȴ�.
		D3D11_SHADER_DESC shaderDesc;
		HR(_reflection->GetDesc(&shaderDesc));
		const UINT totalNumCBuffers = shaderDesc.ConstantBuffers;

		//��� ���۰� ���� ���, �ٷ� ����.
		if (totalNumCBuffers == 0)
		{
			return;
		}

		//���߿� ������������ �ٲ�� �ȴٸ�, ���� ���� �������� ���� ����.
		//�ƴϸ� ����Ʈ�� �����ϴ� CBuffer�� �ִٸ�, �� ���� �ݿ��Ǿ �ٲ��� �Ѵ�.
		//-> 240220 : ���� ������ b8�� ����� �� �ְ� �ٲ����!
		// �� Assert�� ���� �� Shader�� CBuffer���� �����ϱ� ������.
		//assert(totalNumCBuffers == 1 && "Paragon Engine : ��� ���� �ϳ�¥���� Fix (Ŭ���̾�Ʈ ��)");

		//Constant Buffer�� �ϳ� �������� ������ �ϵ��ڵ�.
		//�ٸ�, ������ ���� ���� CBuffer�� �߰��ȴٸ�, �̸� ���� ���� �ȵȴ�.
		//�̸� ���� ����, Register�� ���� �� �� �ְ�!
		ID3D11ShaderReflectionConstantBuffer* cbReflection = nullptr;

		D3D11_SHADER_BUFFER_DESC tConstantBufferDesc;
		ZeroMemory(&tConstantBufferDesc, sizeof(D3D11_SHADER_BUFFER_DESC));

		D3D11_SHADER_INPUT_BIND_DESC tShaderInputBindDesc;
		ZeroMemory(&tShaderInputBindDesc, sizeof(D3D11_SHADER_INPUT_BIND_DESC));

		bool tOnceWasEight = false;
		//std::vector<unsigned int> tTempVec;
		//���̴��� ������ ������ .cso�� ���Խ�Ű�� ����. �� ������ ���� �߻�!

		//Ŭ���̾�Ʈ �� Constant Buffer�� �ǵ帮�� �ʰ� �������� ���ؼ�.
		for (int i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT; i++)
		{
			cbReflection = nullptr;
			cbReflection = _reflection->GetConstantBufferByIndex(i);

			ZeroMemory(&tConstantBufferDesc, sizeof(D3D11_SHADER_BUFFER_DESC));
			//HR(cbReflection->GetDesc(&tConstantBufferDesc));
			if (FAILED(cbReflection->GetDesc(&tConstantBufferDesc))) 
			{
				continue;
			}

			//Register Number ���.
			ZeroMemory(&tShaderInputBindDesc, sizeof(D3D11_SHADER_INPUT_BIND_DESC));
			HR(_reflection->GetResourceBindingDescByName(tConstantBufferDesc.Name, &tShaderInputBindDesc));
			
			//if (tShaderInputBindDesc.BindPoint >= CBUFFER_CLIENT_START_REGISTER)
			if (tShaderInputBindDesc.BindPoint == CBUFFER_CLIENT_START_REGISTER)
			{
				//�ϳ��� ������ �������� Register Number�� ��� ���۰� �ִٸ�, �ٷ� ������!
				tOnceWasEight = true;
				break;
			}
		}

		assert(tOnceWasEight && "���ϴ� CBuffer�� ������ �ѹ��� �о���� ���ߴٴ� ��");

		//�Ϸ�Ǿ�����, Material�� �ʿ��� ���� �޾ƿͼ� �����Ѵ�.
		_matPropConstantBufferList->SetByteCount(tConstantBufferDesc.Size);
		_matPropConstantBufferList->SetConstantBufferName(tConstantBufferDesc.Name);
		_matPropConstantBufferList->SetRegisterNumberCount(tShaderInputBindDesc.BindPoint);

		//Reflection�� nullptr�� �ƴ϶�� ���� Ȯ��!
		assert(cbReflection != nullptr);

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
			&& "����Ʈ�Ǵ� ���� ������ �ƴ�.");

		UINT tCount = shaderTypeDesc->Columns;
		assert(tCount >= 1 && "�ƴϸ� ī��Ʈ�� 0���̴�.");

		ConstantBufferVariableProp tProp;
		tProp._name = shaderVarDesc->Name;
		tProp._size = shaderVarDesc->Size;
		tProp._startOffset = shaderVarDesc->StartOffset;

		//���߿� ������ �� �� �ֵ��� ������� ���.
		_matPropConstantBufferList->_varRecord.push_back(shaderVarDesc->Name);

		if (shaderTypeDesc->Type == D3D_SVT_BOOL && tCount == 1)
		{
			_matPropConstantBufferList->_boolPropList.push_back(std::make_pair(tProp, false));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_UINT && tCount == 1)
		{
			_matPropConstantBufferList->_uintPropList.push_back(std::make_pair(tProp, 0));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_INT && tCount == 1)
		{
			_matPropConstantBufferList->_intPropList.push_back(std::make_pair(tProp, 0));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 1)
		{
			_matPropConstantBufferList->_floatPropList.push_back(std::make_pair(tProp, 0.f));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 2)
		{
			_matPropConstantBufferList->_vec2PropList.push_back(std::make_pair(tProp, float2{ 0.f,0.f }));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 3)
		{
			_matPropConstantBufferList->_vec3PropList.push_back(std::make_pair(tProp, float3{ 0.f,0.f,0.f }));
		}
		else if (shaderTypeDesc->Type == D3D_SVT_FLOAT && tCount == 4)
		{
			_matPropConstantBufferList->_vec4PropList.push_back(std::make_pair(tProp, float4{ 0.f,0.f,0.f,0.f }));
		}
		else
		{
			assert(false && "ȣȯ���� �ʴ� ������ Variable.");
		}
	}

	void BaseShader::GetTextureBufferVariableInfo()
	{
		//�ý��ۿ��� Ŭ���̾�Ʈ���� ����� Register���� ���� �ٲ� �� �ְ� �ȴ�.
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

						//������ �˱� ���ؼ� ����.
						_matPropTexturesList->_varRecord.push_back(tBindDesc.Name);

						if (SUPPORTED_MIN_TEXTURE_RETURN_TYPE_ENUM <= tBindDesc.ReturnType &&
							SUPPORTED_MAX_TEXTURE_RETURN_TYPE_ENUM >= tBindDesc.ReturnType)
						{
							tProp._resReturnType = static_cast<eResourceReturnType>(tBindDesc.ReturnType);
						}
						else
						{
							assert(false && "Unsupported Format");
						}

						//���� ���� � Ÿ������ ��󳻾� �Ѵ�.
						if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE1D)
						{
							_matPropTexturesList->_texture1DPropList.push_back(std::make_pair(tProp,"TextureName"));
						}
						else if(tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE2D)
						{
							_matPropTexturesList->_texture2DPropList.push_back(std::make_pair(tProp, "TextureName"));
						}
						else if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURE2DARRAY)
						{
							_matPropTexturesList->_texture2DArrayPropList.push_back(std::make_pair(tProp, "TextureName"));
						}
						else if (tBindDesc.Dimension == D3D_SRV_DIMENSION_TEXTURECUBE)
						{
							_matPropTexturesList->_textureCubePropList.push_back(std::make_pair(tProp, "TextureName"));
						}
						else
						{
							assert(false && "Unsupported Resource Dimension");
						}
					}
				}
				break;
				default: 
				break; //���÷��� �ٸ� ���ҽ� Ÿ�Ե���, �̹� ������� ��Ͽ��� �� �� ���� ���̴�.
			}
		}
	}
}
