#include "PixelShader.h"

namespace Pg
{
	PixelShader::PixelShader(const std::wstring& path) :
		_filePath(path)
	{
		_matPropList = std::make_unique<MaterialPropertyList>();
	}

	PixelShader::~PixelShader()
	{

	}

}