#pragma once
#define DEFAULT_PATH_NULL L"NULL"

//�⺻������ ������ ����� �� �ִ� ���������� ������ t25�̴�.
#define TEXTURES_CLIENT_START_REGISTER 25
#define CBUFFER_CLIENT_START_REGISTER 8
#define SUPPORTED_MIN_TEXTURE_RETURN_TYPE_ENUM 1
#define SUPPORTED_MAX_TEXTURE_RETURN_TYPE_ENUM 5

namespace Pg
{
	enum class eShaderType
	{
		_VS,
		_PS
	};

	enum class eResourceReturnType : unsigned int
	{
		//D3D_RESOURCE_RETURN_TYPE�� 1��1 ����.
		PG_RETURN_TYPE_UNORM = 1,
		PG_RETURN_TYPE_SNORM = 2,
		PG_RETURN_TYPE_SINT = 3,
		PG_RETURN_TYPE_UINT = 4,
		PG_RETURN_TYPE_FLOAT = 5
		//�������� �������� ���� ����.
	};
}
