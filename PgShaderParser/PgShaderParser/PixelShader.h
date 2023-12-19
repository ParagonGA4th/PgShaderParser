#pragma once
#include <string>
#include <memory>
namespace Pg
{
	class MaterialPropertyList;

	//자신이 생성되었다는 것 = 로드되었다는 것.
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

