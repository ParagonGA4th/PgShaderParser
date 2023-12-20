#include "PixelShader.h"
#include "ConstantBufferPropertyList.h"
#include <filesystem>
#include <cassert>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>

#pragma comment(lib, "Dxgi.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

namespace Pg
{
	PixelShader::PixelShader(const std::wstring& path) :
		BaseShader(path)
	{
	
	}

	PixelShader::~PixelShader()
	{

	}
}