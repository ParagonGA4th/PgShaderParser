#pragma once
#include "BaseShader.h"

namespace Pg
{
	//�ڽ��� �����Ǿ��ٴ� �� = �ε�Ǿ��ٴ� ��.
	class PixelShader : public BaseShader
	{
	public:
		PixelShader(const std::wstring& path);
		~PixelShader();
	};
}

