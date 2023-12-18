#pragma once
#include <string>

namespace Pg
{
	class TextHelper
	{
	public:
		static std::string TextKR(const std::string& krString);
	};
}

#define T_KR(tInput) Pg::TextHelper::TextKR(tInput).c_str()