#pragma once
#include <vector>
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
		//Variable�� Index��� ������ variable string�� �����Ѵ�.
		std::vector<std::string> _varRecord;

		//���ʷ� Variable Name / Value
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


