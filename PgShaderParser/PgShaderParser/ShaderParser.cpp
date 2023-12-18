#include "ShaderParser.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <cassert>

namespace Pg
{
	ShaderParser::ShaderParser()
	{

	}

	ShaderParser::~ShaderParser()
	{

	}

	void ShaderParser::Initialize()
	{

	}

	void ShaderParser::Finalize()
	{
		Reset();
	}

	bool ShaderParser::LoadVertexShader(const std::wstring& shaderPath)
	{
		//기존에 있던 정보 싹 정리.
		//Reset();
		//
		////HLSL Compile해서 읽어오기.
		//HRESULT hr = S_OK;
		//ID3DBlob* tShaderByteCode = nullptr;
		//ID3DBlob* tIfErrorBlob = nullptr;
		//
		////컴파일하는 Flag.
		//UINT tCompileFlags = 0;
		//hr = D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		//	"VS", "vs_5_0", tCompileFlags, 0, &tShaderByteCode, &tIfErrorBlob);
		//assert(SUCCEEDED(hr));
		//
		////실제 Reflection D3D 코드.
		//ID3D11ShaderReflection* reflection = nullptr;
		//
		//hr = D3DReflect(tShaderByteCode->GetBufferPointer(), 
		//	tShaderByteCode->GetBufferSize(),
		//	IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&reflection));
		//assert(SUCCEEDED(hr));

		return false;
	}

	bool ShaderParser::LoadPixelShader(const std::wstring& shaderPath)
	{
		return false;
	}

	void ShaderParser::Reset()
	{
		for (int i = 0; i < _boolPropList.size(); i++) { _boolPropList.pop(); }
		for (int i = 0; i < _uintPropList.size(); i++) { _uintPropList.pop(); }
		for (int i = 0; i < _intPropList.size(); i++) { _intPropList.pop(); }
		for (int i = 0; i < _floatPropList.size(); i++) { _floatPropList.pop(); }
		for (int i = 0; i < _vec2PropList.size(); i++) { _vec2PropList.pop(); }
		for (int i = 0; i < _vec3PropList.size(); i++) { _vec3PropList.pop(); }
		for (int i = 0; i < _vec4PropList.size(); i++) { _vec4PropList.pop(); }
		for (int i = 0; i < _colorPropList.size(); i++) { _colorPropList.pop(); }
		for (int i = 0; i < _texture2DPropList.size(); i++) { _texture2DPropList.pop(); }
		for (int i = 0; i < _textureCubePropList.size(); i++) { _textureCubePropList.pop(); }
	}

	bool ShaderParser::RetrieveSingleBoolProp(std::string& varName, bool& value)
	{
		if (_boolPropList.empty()) { return false; }

		auto tRes = _boolPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_boolPropList.pop();
	}

	bool ShaderParser::RetrieveSingleUnsignedIntProp(std::string& varName, unsigned int& value)
	{
		if (_uintPropList.empty()) { return false; }

		auto tRes = _uintPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_uintPropList.pop();
	}

	bool ShaderParser::RetrieveSingleIntProp(std::string& varName, int& value)
	{
		if (_intPropList.empty()) { return false; }

		auto tRes = _intPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_intPropList.pop();
	}

	bool ShaderParser::RetrieveSingleFloatProp(std::string& varName, float& value)
	{
		if (_floatPropList.empty()) { return false; }

		auto tRes = _floatPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_floatPropList.pop();
	}

	bool ShaderParser::RetrieveSingleVector2Prop(std::string& varName, float2& value)
	{
		if (_vec2PropList.empty()) { return false; }

		auto tRes = _vec2PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec2PropList.pop();
	}

	bool ShaderParser::RetrieveSingleVector3Prop(std::string& varName, float3& value)
	{
		if (_vec3PropList.empty()) { return false; }

		auto tRes = _vec3PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec3PropList.pop();
	}

	bool ShaderParser::RetrieveSingleVector4Prop(std::string& varName, float4& value)
	{
		if (_vec4PropList.empty()) { return false; }

		auto tRes = _vec4PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec4PropList.pop();
	}

	bool ShaderParser::RetrieveSingleColorProp(std::string& varName, color4& value)
	{
		if (_colorPropList.empty()) { return false; }

		auto tRes = _colorPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_colorPropList.pop();
	}

	bool ShaderParser::RetrieveSingleTexture2DProp(std::string& varName, std::string& value)
	{
		if (_texture2DPropList.empty()) { return false; }

		auto tRes = _texture2DPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_texture2DPropList.pop();
	}

	bool ShaderParser::RetrieveSingleTextureCubeProp(std::string& varName, std::string& value)
	{
		if (_textureCubePropList.empty()) { return false; }

		auto tRes = _textureCubePropList.top();
		varName = tRes.first;
		value = tRes.second;

		_textureCubePropList.pop();
	}

}