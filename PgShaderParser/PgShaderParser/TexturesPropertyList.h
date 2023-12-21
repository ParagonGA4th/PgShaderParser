#pragma once
#include <stack>
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
		bool RetrieveSingleTexture1DProp(TexturesVariableProp& varName, std::string& value);
		bool RetrieveSingleTexture2DProp(TexturesVariableProp& varName, std::string& value);
		bool RetrieveSingleTexture2DArrayProp(TexturesVariableProp& varName, std::string& value);
		bool RetrieveSingleTextureCubeProp(TexturesVariableProp& varName, std::string& value);

	private:
		//Variable Name / Value/
		std::stack<std::pair<TexturesVariableProp, std::string>> _texture1DPropList; //Texture 1D -> �ؽ��� �̸��� ���.
		std::stack<std::pair<TexturesVariableProp, std::string>> _texture2DPropList; //Texture 2D -> �ؽ��� �̸��� ���.
		std::stack<std::pair<TexturesVariableProp, std::string>> _texture2DArrayPropList; //Texture2DArray -> �ؽ��� �̸��� ���.
		std::stack<std::pair<TexturesVariableProp, std::string>> _textureCubePropList; //TextureCube -> �ؽ��� �̸��� ���.
	};
}


