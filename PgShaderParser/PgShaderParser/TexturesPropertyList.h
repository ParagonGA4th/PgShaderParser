#pragma once
#include <vector>
#include <string>
#include <filesystem>

#include "PgData.h"

namespace Pg
{
	class TexturesPropertyList
	{
		friend class BaseShader;
	public:
		void Reset();

	public:
		//Variable�� Index��� ������ variable string�� �����Ѵ�.
		std::vector<std::string> _varRecord;

		//Variable Name / Value/
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture1DPropList; //Texture 1D -> �ؽ��� �̸��� ���.
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture2DPropList; //Texture 2D -> �ؽ��� �̸��� ���.
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture2DArrayPropList; //Texture2DArray -> �ؽ��� �̸��� ���.
		std::vector<std::pair<TexturesVariableProp, std::string>> _textureCubePropList; //TextureCube -> �ؽ��� �̸��� ���.
	};
}


