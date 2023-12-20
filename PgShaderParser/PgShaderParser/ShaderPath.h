#pragma once
#include <string>

//ShaderPath ����.
///DEPRECATED, .cso�� �Ľ��ϱ�� ��.
namespace Pg
{
	class ShaderPath
	{
	public:
		static std::string GetRelativeFolder();
		static void SetRelativeFolder(const std::string& relFolder);

		//���� ��� ���, Absolute Path ��ȯ.
		static std::string RelativeToAbsolutePath(const std::string& baseFolderPath, const std::string& relIncludePath);
		
	private:
		//��� ��ΰ� ���� String + �ö� ����.
		static void RelUpCountString(const std::string& originIncludeStr, std::string& outRemovedStr, int& outRelUpCount);
	private:
		static std::string _relativeFolder;
	};
}
