#pragma once
#include <string>

namespace Pg
{
	class VertexShader;
	class PixelShader;
}

namespace Pg
{
	class Material
	{
	public:
		Material();

		std::wstring GetFilePath();
		std::wstring GetFileName();
	
		bool SetVertexShader(VertexShader* shader) { _vs = shader; }
		bool SetPixelShader(PixelShader* shader) { _ps = shader; }

		bool IsVSActive() { return _vs != nullptr; }
		bool IsPSActive() { return _ps != nullptr; }

		VertexShader* ConfideGetVertexShader();
		PixelShader* ConfideGetPixelShader();

		//���� ���� ��ȯ.
		bool Generate();

	private:
		std::wstring _filePath;

	private:
		VertexShader* _vs = nullptr;
		PixelShader* _ps = nullptr;
	};
}


