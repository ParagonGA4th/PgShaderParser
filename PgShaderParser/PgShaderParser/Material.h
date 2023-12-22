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

		void SetFilePath(const std::wstring& fPath);
		std::wstring GetFilePath();
		std::wstring GetFileName();
	
		void SetVertexShader(VertexShader* shader) {  _vs = shader; }
		void SetPixelShader(PixelShader* shader) { _ps = shader; }

		bool IsVSActive() { return _vs != nullptr; }
		bool IsPSActive() { return _ps != nullptr; }

		VertexShader* ConfideGetVertexShader();
		PixelShader* ConfideGetPixelShader();

		//성공 여부 반환.
		bool Generate(const std::wstring& filePath);

	private:
		std::wstring _filePath;

	private:
		VertexShader* _vs = nullptr;
		PixelShader* _ps = nullptr;
	};
}


