#pragma once
#include "BaseShader.h"

namespace Pg
{
	//�ڽ��� �����Ǿ��ٴ� �� = �ε�Ǿ��ٴ� ��.
	class VertexShader : public BaseShader
	{
	public:
		VertexShader(const std::wstring& path);
		~VertexShader();
	};
}


