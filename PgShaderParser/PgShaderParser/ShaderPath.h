#pragma once
#include <string>

//ShaderPath 보관.
///DEPRECATED, .cso를 파싱하기로 함.
namespace Pg
{
	class ShaderPath
	{
	public:
		static std::string GetRelativeFolder();
		static void SetRelativeFolder(const std::string& relFolder);

		//들어온 경로 기반, Absolute Path 반환.
		static std::string RelativeToAbsolutePath(const std::string& baseFolderPath, const std::string& relIncludePath);
		
	private:
		//상대 경로가 빠진 String + 올라간 개수.
		static void RelUpCountString(const std::string& originIncludeStr, std::string& outRemovedStr, int& outRelUpCount);
	private:
		static std::string _relativeFolder;
	};
}
