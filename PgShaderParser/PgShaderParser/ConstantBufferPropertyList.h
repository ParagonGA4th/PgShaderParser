#pragma once
#include <stack>
#include <string>
#include <filesystem>

#include "PgData.h"

//Constant Buffer 하나에 대응.
//현재로서는 Material에 Constant Buffer 하나 이상 지원할 이유 X.

namespace Pg
{
	class ConstantBufferPropertyList
	{
		friend class BaseShader;
	public:
		ConstantBufferPropertyList();
		~ConstantBufferPropertyList();

		void Reset();
		void SetByteCount(unsigned int byteCount);
		unsigned int GetByteCount();

		void SetConstantBufferName(const std::string& cBufName);
		std::string GetConstantBufferName();
	public:

	public:
		//Return Val : 가져오는 것을 성공했는지
		//매개변수 : 바인딩한 Variable Name / Value.
		bool RetrieveSingleBoolProp(ConstantBufferVariableProp& varName, bool& value);
		bool RetrieveSingleUnsignedIntProp(ConstantBufferVariableProp& varName, unsigned int& value);
		bool RetrieveSingleIntProp(ConstantBufferVariableProp& varName, int& value);
		bool RetrieveSingleFloatProp(ConstantBufferVariableProp& varName, float& value);
		bool RetrieveSingleVector2Prop(ConstantBufferVariableProp& varName, float2& value);
		bool RetrieveSingleVector3Prop(ConstantBufferVariableProp& varName, float3& value);
		bool RetrieveSingleVector4Prop(ConstantBufferVariableProp& varName, float4& value);
		
	private:
		size_t _byteCount = 0;
		std::string _constantBufferName;

		//차례로 Variable Name / Value
		std::stack<std::pair<ConstantBufferVariableProp, bool>>		_boolPropList;
		std::stack<std::pair<ConstantBufferVariableProp, unsigned int>> _uintPropList;
		std::stack<std::pair<ConstantBufferVariableProp, int>>			 _intPropList;
		std::stack<std::pair<ConstantBufferVariableProp, float>>		_floatPropList;
		std::stack<std::pair<ConstantBufferVariableProp, float2>>		_vec2PropList;
		std::stack<std::pair<ConstantBufferVariableProp, float3>>		_vec3PropList;
		std::stack<std::pair<ConstantBufferVariableProp, float4>>		_vec4PropList;
	};
}


