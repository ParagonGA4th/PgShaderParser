#pragma once
#include "BaseShader.h"

namespace Pg
{
	//자신이 생성되었다는 것 = 로드되었다는 것.
	class VertexShader : public BaseShader
	{
	public:
		VertexShader(const std::wstring& path);
		~VertexShader();
	};
}


