#pragma once
#include <string>
#include <memory>

struct ID3D11ShaderReflection;
//struct D3D11_SHADER_VARIABLE_DESC;
//struct D3D11_SHADER_TYPE_DESC;
struct _D3D11_SHADER_VARIABLE_DESC;
struct _D3D11_SHADER_TYPE_DESC;

namespace Pg
{
	class ConstantBufferPropertyList;
	class TexturesPropertyList;

	class BaseShader
	{
	public:
		BaseShader(const std::wstring& path);
		~BaseShader();

		void LoadReflection();

		std::wstring GetFilePath();
		std::wstring GetFileName();

	protected:
		void GetConstantBufferVariableInfo();
		void GetTextureBufferVariableInfo();

	protected:
		void ProcessConstantBufferVariables(const _D3D11_SHADER_VARIABLE_DESC* shaderVarDesc, const _D3D11_SHADER_TYPE_DESC* shaderTypeDesc);

	protected:
		std::wstring _filePath;
		std::unique_ptr<ConstantBufferPropertyList> _matPropConstantBufferList;
		std::unique_ptr<TexturesPropertyList> _matPropTexturesList;

	protected:
		::ID3D11ShaderReflection* _reflection;
	};
}


