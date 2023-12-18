#pragma once
#include <stack>
#include <string>

#include "PgData.h"

namespace Pg
{
	class ShaderParser
	{
	public:
		ShaderParser();
		~ShaderParser();

		void Initialize();
		void Finalize();

		bool Load(const std::string shaderPath);
		void Reset();

		//Return Val : 가져오는 것을 성공했는지
		//매개변수 : 바인딩한 Variable Name / Value.
		bool RetrieveSingleBoolProp(std::string& varName, bool& value);
		bool RetrieveSingleUnsignedIntProp(std::string& varName, unsigned int& value);
		bool RetrieveSingleIntProp(std::string& varName, int& value);
		bool RetrieveSingleFloatProp(std::string& varName, float& value);
		bool RetrieveSingleVector2Prop(std::string& varName, float2& value);
		bool RetrieveSingleVector3Prop(std::string& varName, float3& value);
		bool RetrieveSingleVector4Prop(std::string& varName, float4& value);
		bool RetrieveSingleColorProp(std::string& varName, color4& value);
		bool RetrieveSingleTexture2DProp(std::string& varName, std::string& value);
		bool RetrieveSingleTextureCubeProp(std::string& varName, std::string& value);

	private:
		//차례로 Variable Name / Value
		std::stack<std::pair<std::string, bool>>		_boolPropList;
		std::stack<std::pair<std::string, unsigned int>> _uintPropList;
		std::stack<std::pair<std::string, int>>			 _intPropList;
		std::stack<std::pair<std::string, float>>		_floatPropList;
		std::stack<std::pair<std::string, float2>>		_vec2PropList;
		std::stack<std::pair<std::string, float3>>		_vec3PropList;
		std::stack<std::pair<std::string, float4>>		_vec4PropList;
		std::stack<std::pair<std::string, color4>>		_colorPropList;
		std::stack<std::pair<std::string, std::string>> _texture2DPropList; //Texture 2D -> 텍스쳐 이름을 기록.
		std::stack<std::pair<std::string, std::string>> _textureCubePropList; //TextureCube -> 텍스쳐 이름을 기록.
	};
}


