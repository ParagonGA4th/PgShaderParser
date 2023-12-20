#include "TexturesPropertyList.h"
namespace Pg
{
	void TexturesPropertyList::Reset()
	{
		for (int i = 0; i < _texture2DPropList.size(); i++) { _texture2DPropList.pop(); }
		for (int i = 0; i < _textureCubePropList.size(); i++) { _textureCubePropList.pop(); }
	}

	bool TexturesPropertyList::RetrieveSingleTexture2DProp(std::string& varName, std::string& value)
	{
		if (_texture2DPropList.empty()) { return false; }

		auto tRes = _texture2DPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_texture2DPropList.pop();
	}

	bool TexturesPropertyList::RetrieveSingleTextureCubeProp(std::string& varName, std::string& value)
	{
		if (_textureCubePropList.empty()) { return false; }

		auto tRes = _textureCubePropList.top();
		varName = tRes.first;
		value = tRes.second;

		_textureCubePropList.pop();
	}

}

