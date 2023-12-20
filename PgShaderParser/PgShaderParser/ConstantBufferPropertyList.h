#pragma once
#include <stack>
#include <string>
#include <filesystem>

#include "PgData.h"

//Constant Buffer �ϳ��� ����.
//����μ��� Material�� Constant Buffer �ϳ� �̻� ������ ���� X.

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
		//Return Val : �������� ���� �����ߴ���
		//�Ű����� : ���ε��� Variable Name / Value.
		bool RetrieveSingleBoolProp(std::string& varName, bool& value);
		bool RetrieveSingleUnsignedIntProp(std::string& varName, unsigned int& value);
		bool RetrieveSingleIntProp(std::string& varName, int& value);
		bool RetrieveSingleFloatProp(std::string& varName, float& value);
		bool RetrieveSingleVector2Prop(std::string& varName, float2& value);
		bool RetrieveSingleVector3Prop(std::string& varName, float3& value);
		bool RetrieveSingleVector4Prop(std::string& varName, float4& value);
		
	private:
		size_t _byteCount = 0;
		std::string _constantBufferName;

		//���ʷ� Variable Name / Value
		std::stack<std::pair<std::string, bool>>		_boolPropList;
		std::stack<std::pair<std::string, unsigned int>> _uintPropList;
		std::stack<std::pair<std::string, int>>			 _intPropList;
		std::stack<std::pair<std::string, float>>		_floatPropList;
		std::stack<std::pair<std::string, float2>>		_vec2PropList;
		std::stack<std::pair<std::string, float3>>		_vec3PropList;
		std::stack<std::pair<std::string, float4>>		_vec4PropList;
	};
}


