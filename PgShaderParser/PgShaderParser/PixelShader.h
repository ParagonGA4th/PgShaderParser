#pragma once
#include <string>
#include <memory>
namespace Pg
{
	class MaterialPropertyList;

	//�ڽ��� �����Ǿ��ٴ� �� = �ε�Ǿ��ٴ� ��.
	class PixelShader
	{
	public:
		PixelShader(const std::wstring& path);
		~PixelShader();

		std::wstring GetFilePath() { return _filePath; }

	private:
		std::wstring _filePath;
		std::unique_ptr<MaterialPropertyList> _matPropList;
	};
}

