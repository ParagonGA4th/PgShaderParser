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
		bool RetrieveSingleTexture2DProp(std::string& varName, std::string& value);
		bool RetrieveSingleTextureCubeProp(std::string& varName, std::string& value);

	private:
		std::stack<std::pair<std::string, std::string>> _texture2DPropList; //Texture 2D -> �ؽ��� �̸��� ���.
		std::stack<std::pair<std::string, std::string>> _textureCubePropList; //TextureCube -> �ؽ��� �̸��� ���.
	};
}


