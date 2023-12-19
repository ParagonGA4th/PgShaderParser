#include "Material.h"
#include <cassert>
#include <filesystem>

namespace Pg
{
	Material::Material()
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
		return true;
	}

	std::wstring Material::GetFilePath()
	{
		return _filePath;
	}

	std::wstring Material::GetFileName()
	{
		return std::filesystem::path(_filePath).filename();
	}

}