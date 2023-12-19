#pragma once
#include <string>
#include <memory>

struct ID3D11ShaderReflection;

namespace Pg
{
	class MaterialPropertyList;

	//자신이 생성되었다는 것 = 로드되었다는 것.
	class VertexShader
	{
	public:
		VertexShader(const std::wstring& path);
		~VertexShader();

		void LoadReflection();

		std::wstring GetFilePath();
		std::wstring GetFileName();
	private:
		std::wstring _filePath;
		std::unique_ptr<MaterialPropertyList> _matPropList;

	private:
		::ID3D11ShaderReflection* _reflection;
	};
}


