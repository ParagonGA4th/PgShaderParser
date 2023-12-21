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
		//Variable Name / Value/
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture1DPropList; //Texture 1D -> 텍스쳐 이름을 기록.
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture2DPropList; //Texture 2D -> 텍스쳐 이름을 기록.
		std::vector<std::pair<TexturesVariableProp, std::string>> _texture2DArrayPropList; //Texture2DArray -> 텍스쳐 이름을 기록.
		std::vector<std::pair<TexturesVariableProp, std::string>> _textureCubePropList; //TextureCube -> 텍스쳐 이름을 기록.
	};
}


