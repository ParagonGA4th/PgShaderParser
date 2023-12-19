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
		bool LoadVertexShader(const std::wstring& shaderPath);
		bool LoadPixelShader(const std::wstring& shaderPath);

		bool IsVSActive() { return _vs != nullptr; }
		bool IsPSActive() { return _ps != nullptr; }

		VertexShader* ConfideGetVertexShader();
		PixelShader* ConfideGetPixelShader();

		//���� ���� ��ȯ.
		bool Generate();

	private:
		VertexShader* _vs = nullptr;
		PixelShader* _ps = nullptr;
	};
}


