#pragma once
#include <string>
#include "PgDefineEnums.h"

namespace Pg
{
	//Vector�� �����ε带 ���ϱ� ����. (vector<bool>)
	struct BoolWrapper
	{
		BoolWrapper(bool val) { _value = val; }
		bool _value = false;
	};

	struct ConstantBufferVariableProp
	{
		ConstantBufferVariableProp() = default;

		std::string _name;
		unsigned int _size = 0;
		unsigned int _startOffset = 0;
	};

	struct TexturesVariableProp
	{
		TexturesVariableProp() = default;

		std::string _name;
		eResourceReturnType _resReturnType; //Ÿ����ü��, ���� ��� D3D�� X (������ ��κ� 4��¥���ϰ�)
		unsigned int _registerCnt = 0;
	};

	struct float2
	{
		float2() = default;
		float2(float tX, float tY) : x(tX), y(tY) {}

		union
		{
			float _v[2];
			struct
			{
				float x;
				float y;
			};
		};
	};

	struct float3
	{
		float3() = default;
		float3(float tX, float tY, float tZ) : x(tX), y(tY), z(tZ) {}

		union
		{
			float _v[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	};

	struct float4
	{
		float4() = default;
		float4(float tX, float tY, float tZ, float tW) : x(tX), y(tY), z(tZ), w(tW) {}

		union
		{
			float _v[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};
}
