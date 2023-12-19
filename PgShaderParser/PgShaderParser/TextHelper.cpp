#include "TextHelper.h"
#include <windows.h>
#include <cassert>

namespace Pg
{
	std::string TextHelper::TextKR(const std::string& krString)
	{
		//assert(krString.size() < 255);
		wchar_t warr[256];
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)krString.c_str(), -1, warr, 256);
		char carr[256];
		memset(carr, '\0', sizeof(carr));
		WideCharToMultiByte(CP_UTF8, 0, warr, -1, carr, 256, NULL, NULL);
		return carr;
	}

	std::string TextHelper::TextKR_W(const std::wstring& krString)
	{
		char carr[256];
		memset(carr, '\0', sizeof(carr));
		WideCharToMultiByte(CP_UTF8, 0, krString.c_str(), -1, carr, 256, NULL, NULL);
		return carr;
	}

	std::wstring TextHelper::AnsiToWString(const char* ansiString)
	{
		wchar_t buffer[512];
		int res = MultiByteToWideChar(CP_ACP, 0, ansiString, -1, buffer, 512);
		return std::wstring(buffer);
	}

}
