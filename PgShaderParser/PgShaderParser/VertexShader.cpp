#include "VertexShader.h"

namespace Pg
{
	VertexShader::VertexShader(const std::wstring& path) :
		_filePath(path)
	{
		_matPropList = std::make_unique<MaterialPropertyList>();
	}

	VertexShader::~VertexShader()
	{

	}

}