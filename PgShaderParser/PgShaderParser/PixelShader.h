#pragma once
#include <string>
#include <memory>

struct ID3D11ShaderReflection;

namespace Pg
{
	class MaterialPropertyList;

	//�ڽ��� �����Ǿ��ٴ� �� = �ε�Ǿ��ٴ� ��.
	class PixelShader
	{
	public:
		PixelShader(const std::wstring& path);
		~PixelShader();

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

