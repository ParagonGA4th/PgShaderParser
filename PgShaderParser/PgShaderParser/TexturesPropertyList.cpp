#include "TexturesPropertyList.h"
namespace Pg
{
	void TexturesPropertyList::Reset()
	{
		_texture1DPropList.clear();
		_texture2DPropList.clear();
		_texture2DArrayPropList.clear();
		_textureCubePropList.clear();
	}
}

