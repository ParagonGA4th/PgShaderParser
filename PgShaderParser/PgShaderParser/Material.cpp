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

	}

}