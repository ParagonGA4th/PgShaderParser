#pragma once
#include "PgDefineEnums.h"
#include <string>

namespace Pg
{
	//급하게 Enum->String 도와주는 헬퍼.
	class EnumHelper
	{
	public:
		static std::string ToString(eResourceReturnType res);
	};

	std::string EnumHelper::ToString(eResourceReturnType res)
	{
		std::string tRet = "";
		switch (res)
		{
			case eResourceReturnType::PG_RETURN_TYPE_UNORM:
			{
				tRet = "PG_RETURN_TYPE_UNORM";
			}
			break;
			case eResourceReturnType::PG_RETURN_TYPE_SNORM:
			{
				tRet = "PG_RETURN_TYPE_SNORM";
			}
			break;
			case eResourceReturnType::PG_RETURN_TYPE_SINT:
			{
				tRet = "PG_RETURN_TYPE_SINT";
			}
			break;
			case eResourceReturnType::PG_RETURN_TYPE_UINT:
			{
				tRet = "PG_RETURN_TYPE_UINT";
			}
			break;
			case eResourceReturnType::PG_RETURN_TYPE_FLOAT:
			{
				tRet = "PG_RETURN_TYPE_FLOAT";
			}
			break;
		}
		return tRet;
	}

}
