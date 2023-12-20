#include "ShaderPath.h"
#include <filesystem>
namespace Pg
{
	std::string ShaderPath::_relativeFolder = "";

	std::string ShaderPath::GetRelativeFolder()
	{
		return _relativeFolder;
	}

	void ShaderPath::SetRelativeFolder(const std::string& relFolder)
	{
		_relativeFolder = relFolder;
	}

	std::string ShaderPath::RelativeToAbsolutePath(const std::string& baseFolderPath, const std::string& relIncludePath)
	{
		std::string tRemovedString = "";
		int tUpCount = 0;
		RelUpCountString(relIncludePath, tRemovedString, tUpCount);

		std::filesystem::path tPath = baseFolderPath;

		for (int i = 0; i < tUpCount; i++)
		{
			tPath = tPath.parent_path();
		}
		std::string tRet = tPath.generic_string();

		tRet = tRet.append("/").append(tRemovedString);
		return tRet;
	}

	void ShaderPath::RelUpCountString(const std::string& originIncludeStr, std::string& outRemovedStr, int& outRelUpCount)
	{
		std::string tStr = originIncludeStr;

		std::string::size_type n1 = 0;
		std::string::size_type n2 = 0;

		std::string target1 = "../";
		std::string target2 = "..\\";

		int tRelUpCount = 0;
		while ((n1 = tStr.find(target1, n1)) != std::string::npos)
		{
			++tRelUpCount;
			n1 += target1.length();
		}

		while ((n2 = tStr.find(target2, n2)) != std::string::npos)
		{
			++tRelUpCount;
			n2 += target2.length();
		}

		std::string subStr = "../";
		std::string subStr2 = "..\\";

		while (true)
		{
			std::string::size_type pos = tStr.find(subStr);

			if (pos == std::string::npos)
			{
				break;
			}

			tStr.erase(pos, subStr.length());
		}

		while (true)
		{
			std::string::size_type pos = tStr.find(subStr2);

			if (pos == std::string::npos)
			{
				break;
			}

			tStr.erase(pos, subStr2.length());
		}

		outRemovedStr = tStr;
		outRelUpCount = tRelUpCount;

		return;
	}
}
