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
}
