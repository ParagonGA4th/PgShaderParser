#pragma once
#include <string>
#include <memory>

namespace Pg
{
	class MaterialPropertyList;

	//�ڽ��� �����Ǿ��ٴ� �� = �ε�Ǿ��ٴ� ��.
	class VertexShader
	{
	public:
		VertexShader(const std::wstring& path);
		~VertexShader();

		std::wstring GetFilePath() { return _filePath; }

	private:
		std::wstring _filePath;
		std::unique_ptr<MaterialPropertyList> _matPropList;
	};
}


