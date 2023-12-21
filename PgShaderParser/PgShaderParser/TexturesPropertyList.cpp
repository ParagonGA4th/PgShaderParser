#include "TexturesPropertyList.h"
namespace Pg
{
	void TexturesPropertyList::Reset()
	{
		for (int i = 0; i < _texture2DPropList.size(); i++) { _texture2DPropList.pop(); }
		for (int i = 0; i < _textureCubePropList.size(); i++) { _textureCubePropList.pop(); }
	}

	bool TexturesPropertyList::RetrieveSingleTexture1DProp(TexturesVariableProp& varName, std::string& value)
	{
		if (_texture1DPropList.empty()) { return false; }

		auto tRes = _texture1DPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_texture1DPropList.pop();
	}

	bool TexturesPropertyList::RetrieveSingleTexture2DProp(TexturesVariableProp& varName, std::string& value)
	{
		if (_texture2DPropList.empty()) { return false; }

		auto tRes = _texture2DPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_texture2DPropList.pop();
	}

	bool TexturesPropertyList::RetrieveSingleTexture2DArrayProp(TexturesVariableProp& varName, std::string& value)
	{
		if (_texture2DArrayPropList.empty()) { return false; }

		auto tRes = _texture2DArrayPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_texture2DArrayPropList.pop();
	}

	bool TexturesPropertyList::RetrieveSingleTextureCubeProp(TexturesVariableProp& varName, std::string& value)
	{
		if (_textureCubePropList.empty()) { return false; }

		auto tRes = _textureCubePropList.top();
		varName = tRes.first;
		value = tRes.second;

		_textureCubePropList.pop();
	}

}

