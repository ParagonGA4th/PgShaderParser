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
		//있다는 것을 이미 확정짓고 호출한 함수.
		assert(_vs != nullptr);
		return _vs;
	}

	Pg::PixelShader* Material::ConfideGetPixelShader()
	{
		//있다는 것을 이미 확정짓고 호출한 함수.
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