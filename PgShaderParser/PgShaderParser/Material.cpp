#include "Material.h"
#include <cassert>

namespace Pg
{
	Material::Material()
	{

	}

	bool Material::LoadVertexShader(const std::wstring& shaderPath)
	{

	}

	bool Material::LoadPixelShader(const std::wstring& shaderPath)
	{

	}

	Pg::VertexShader* Material::ConfideGetVertexShader()
	{
		//�ִٴ� ���� �̹� Ȯ������ ȣ���� �Լ�.
		assert(_vs != nullptr);
		return _vs;
	}

	Pg::PixelShader* Material::ConfideGetPixelShader()
	{
		//�ִٴ� ���� �̹� Ȯ������ ȣ���� �Լ�.
		assert(_ps != nullptr);
		return _ps;
	}

	bool Material::Generate()
	{

	}

}