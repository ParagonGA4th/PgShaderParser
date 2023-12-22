#pragma once
#include <string>

namespace Pg
{
	class TextHelper
	{
	public:
		static std::string TextKR(const std::string& krString);
		static std::string TextKR_W(const std::wstring& krString);
		static std::wstring AnsiToWString(const char* ansiString);
		static std::string WStringToAnsi(const std::wstring& wstring);
	};
}

#define T_KR(tInput) Pg::TextHelper::TextKR(tInput).c_str()
#define T_KR_W(tInput) Pg::TextHelper::TextKR_W(tInput).c_str()