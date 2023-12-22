#pragma once
#include <vector>
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
		friend class BaseShader;
	public:
		ConstantBufferPropertyList();
		~ConstantBufferPropertyList();

		void Reset();
		void SetByteCount(unsigned int byteCount);
		unsigned int GetByteCount();

		void SetConstantBufferName(const std::string& cBufName);
		std::string GetConstantBufferName();

		void SetRegisterNumberCount(unsigned int regNum);
		unsigned int GetRegisterNumberCount();
		
	public:
	private:
		size_t _byteCount = 0;
		std::string _constantBufferName;
		unsigned int _registerNumber = 0;

	public:
		//Variable의 Index대로 들어오는 variable string을 저장한다.
		std::vector<std::string> _varRecord;

		//차례로 Variable Name / Value
		std::vector<std::pair<ConstantBufferVariableProp, bool>>		_boolPropList;
		std::vector<std::pair<ConstantBufferVariableProp, unsigned int>> _uintPropList;
		std::vector<std::pair<ConstantBufferVariableProp, int>>			 _intPropList;
		std::vector<std::pair<ConstantBufferVariableProp, float>>		_floatPropList;
		std::vector<std::pair<ConstantBufferVariableProp, float2>>		_vec2PropList;
		std::vector<std::pair<ConstantBufferVariableProp, float3>>		_vec3PropList;
		std::vector<std::pair<ConstantBufferVariableProp, float4>>		_vec4PropList;
	public:
	};
}


